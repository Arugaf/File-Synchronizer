#include "FileWatcher.hpp"

// TODO: Можно ли переделать с делегирующими конструкторами, чтобы избавиться от копипасты?

FileSynchronizer::FileWatcher::
FileWatcher(std::string path_to_watch,
            int ms_delay) : path_to_watch(std::move(path_to_watch)),
                            mediator(nullptr),
                            delay(ms_delay),
                            ignored_files() {
    if (!std::filesystem::exists(this->path_to_watch)) {
        throw FileWatcherException::InvalidPath(this->path_to_watch);
    }

    for (const auto& file : std::filesystem::recursive_directory_iterator(this->path_to_watch)) {
        if (!IsIgnored(file.path().string())) {
            files[file.path().string()] = std::make_pair(std::filesystem::last_write_time(file),
                                                         file.status().type());
        }
    }
}

FileSynchronizer::FileWatcher::
FileWatcher(std::string path_to_watch,
            std::unordered_set<std::string> ignored_files,
            int ms_delay) : path_to_watch(std::move(path_to_watch)),
                            mediator(nullptr),
                            delay(ms_delay),
                            ignored_files(std::move(ignored_files)) {
    if (!std::filesystem::exists(this->path_to_watch)) {
        throw FileWatcherException::InvalidPath(this->path_to_watch);
    }

    for (const auto& file : std::filesystem::recursive_directory_iterator(this->path_to_watch)) {
        if (!IsIgnored(file.path().string())) {
            files[file.path().string()] = std::make_pair(std::filesystem::last_write_time(file),
                                                         file.status().type());
        }
    }
}

FileSynchronizer::FileWatcher::
FileWatcher(std::string path_to_watch,
            std::unordered_map<std::string,
                               std::pair<std::filesystem::file_time_type,
                                         std::filesystem::file_type>> previous_files,
            int ms_delay) : path_to_watch(std::move(path_to_watch)),
                            mediator(nullptr),
                            delay(ms_delay),
                            ignored_files(),
                            files(std::move(previous_files)) {
    if (!std::filesystem::exists(this->path_to_watch)) {
        throw FileWatcherException::InvalidPath(this->path_to_watch);
    }
}

FileSynchronizer::FileWatcher::
FileWatcher(std::string path_to_watch,
            std::unordered_set<std::string> ignored_files,
            std::unordered_map<std::string,
                               std::pair<std::filesystem::file_time_type,
                                         std::filesystem::file_type>> previous_files,
            int ms_delay) : path_to_watch(std::move(path_to_watch)),
                            mediator(nullptr),
                            delay(ms_delay),
                            ignored_files(std::move(ignored_files)),
                            files(std::move(previous_files)) {
    if (!std::filesystem::exists(this->path_to_watch)) {
        throw FileWatcherException::InvalidPath(this->path_to_watch);
    }
}

FileSynchronizer::FileWatcher::
~FileWatcher() {
    StopWatching();
}

void
FileSynchronizer::FileWatcher::
Watch() {
    while (working) {
        std::this_thread::sleep_for(delay);
        if (watching) {

            // Checking for modified and deleted files
            {
                auto file = files.begin();
                while (file != files.end()) {
                    if (IsExisting(file)) {
                        if (IsChanged(file)) {
                            UpdateFile(file, FileStatus::Changed);
                        }
                        ++file;
                    } else {
                        UpdateFile(file, FileStatus::Deleted);
                    }
                }
            }

            // Checking for newly created files
            for (const auto& file : std::filesystem::recursive_directory_iterator(path_to_watch)) {
                if (files.find(file.path().string()) != files.end() || IsIgnored(file.path().string())) {
                    continue;
                }
                files[file.path().string()] = std::make_pair(std::filesystem::last_write_time(file),
                                                             file.status().type());
                UpdateFile(files.find(file.path().string()), FileStatus::Created);
            }

            // Notify
            if (!changed_files.empty() && working) {
                PauseWatching();
                if (mediator) {
                    mediator->Notify(EventType::FSChanged);
                } else {
                    ContinueWatching();
                }
            }
        }
    }
}

void
FileSynchronizer::FileWatcher::
StartWatching(IMediator* new_mediator) {
    changed_files.clear();
    mediator = new_mediator;
    if (!working) {
        working = true;
        watcher = std::thread(&FileWatcher::Watch, this);
        while (!IsActive());
    }
}

void
FileSynchronizer::FileWatcher::
StopWatching() {
    working = false;
    if (watcher.joinable()) {
        watcher.join();
    }
    while (IsActive());
}

void
FileSynchronizer::FileWatcher::
PauseWatching() {
    watching = false;
}

void
FileSynchronizer::FileWatcher::
ContinueWatching() {
    changed_files.clear();
    watching = true;
}

bool
FileSynchronizer::FileWatcher::
IsIgnored(const std::string& file) const {
    return ignored_files.find(file) != ignored_files.end();
}

std::unordered_map<std::string, FileSynchronizer::FileStatus>
FileSynchronizer::FileWatcher::
GetChangedFiles() const {
    return changed_files;
}

void
FileSynchronizer::FileWatcher::
UpdateFile(const std::string& relative_path) {
    auto file = path_to_watch + relative_path;
    if (std::filesystem::exists(std::filesystem::path(file)) && !IsIgnored(file)) {
        if (files.find(file) == files.end()) {
            files[file] = std::make_pair(std::filesystem::last_write_time(file), std::filesystem::status(file).type());
        } else {
            files[file].first = std::filesystem::last_write_time(file);
        }
    }
}

bool
FileSynchronizer::FileWatcher::
IsWorking()const {
    return working;
}

bool
FileSynchronizer::FileWatcher::
IsWatching() const {
    return watching;
}
