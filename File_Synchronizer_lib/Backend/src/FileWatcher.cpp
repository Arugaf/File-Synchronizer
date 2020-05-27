#include "FileWatcher.h"

#include <utility>

using FileSynchronizer::FileWatcher;
using FileSynchronizer::FileStatuses;

FileWatcher::FileWatcher(path_list paths_to_watch, int ms_delay) :
FileWatcher(std::move(paths_to_watch), FileNames(), ms_delay) {

}

FileWatcher::FileWatcher(path_list paths_to_watch, FileNames ignored_files, int ms_delay) :
FileWatcher(std::move(paths_to_watch), std::move(ignored_files), FilesInfo(), ms_delay) {
    /*for (const auto& path_to_watch : this->paths_to_watch) {
        for (const auto& file : fs::recursive_directory_iterator(path_to_watch)) {
            if (!IsIgnored(file.path())) {
                files[file.path()] = {fs::last_write_time(file), file.status().type()};
                changed_files[file.path()] = FileStatus::Created;
            }
        }
    }*/
}

FileWatcher::FileWatcher(path_list paths_to_watch, FilesInfo previous_files, int ms_delay) :
FileWatcher(std::move(paths_to_watch), FileNames(), std::move(previous_files), ms_delay) {

}

FileWatcher::FileWatcher(path_list paths_to_watch, FileNames ignored_files, FilesInfo previous_files, int ms_delay) :
                         paths_to_watch(std::move(paths_to_watch)),
                         mediator(nullptr),
                         delay(ms_delay),
                         ignored_files(std::move(ignored_files)),
                         files(std::move(previous_files)) {
    for (const auto& path_to_watch : this->paths_to_watch) {
        if (!fs::exists(path_to_watch) || !fs::is_directory(path_to_watch) /*lexical*/) {
            throw FileWatcherException::InvalidPath(path_to_watch);
        }
    }
}

FileWatcher::~FileWatcher() {
    StopWatching();
}

void FileWatcher::Watch() {
    while (working) {
        std::this_thread::sleep_for(delay);
        if (watching) {

            // Checking for modified and deleted files
            {
                auto file = files.begin();
                while (file != files.end()) {
                    if (IsExisting(file)) {
                        if (IsChanged(file)) {
                            UpdateFile(file, FileStatus::Modified);
                        }
                        ++file;
                    } else {
                        UpdateFile(file, FileStatus::Deleted);
                    }
                }
            }

            // Checking for newly created files
            for (const auto& path_to_watch : paths_to_watch) {
                for (const auto& file : fs::recursive_directory_iterator(path_to_watch)) {
                    if (files.find(file.path()) != files.end() || IsIgnored(file.path())) {
                        continue;
                    }
                    files[file.path()] = {fs::last_write_time(file), file.status().type()};
                    UpdateFile(files.find(file.path()), FileStatus::Created);
                }
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

void FileWatcher::StartWatching(const std::shared_ptr<IMediator>& new_mediator) {
    changed_files.clear();
    mediator = new_mediator;
    if (!working) {
        working = true;
        watcher = std::thread(&FileWatcher::Watch, this);
        while (!IsActive());
    }
}

void FileWatcher::StopWatching() {
    working = false;
    if (watcher.joinable()) {
        watcher.join();
    }
    while (IsActive());
}

void FileWatcher::PauseWatching() {
    watching = false;
}

void FileWatcher::ContinueWatching() {
    changed_files.clear();
    watching = true;
}

inline bool FileWatcher::IsIgnored(const std::string& file) const {
    return ignored_files.Find(file);
}

FileStatuses FileWatcher::GetChangedFiles() const {
    return changed_files;
}

bool FileWatcher::IsWorking()const {
    return working;
}

bool FileWatcher::IsWatching() const {
    return watching;
}

bool FileSynchronizer::FileWatcher::IsActive() const {
    return watcher.joinable();
}
