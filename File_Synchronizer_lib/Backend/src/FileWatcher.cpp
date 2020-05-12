//
// Created by arugaf on 11.05.2020.
//

#include "FileWatcher.h"

FileSynchronizer::FileWatcher::FileWatcher(const std::string& path_to_watch,
                                           std::shared_ptr<IMediator> mediator,
                                           int ms_delay) : path_to_watch(std::filesystem::path(path_to_watch)),
                                                           mediator(std::move(mediator)),
                                                           delay(ms_delay) {
    try {
        for (const auto& file : std::filesystem::recursive_directory_iterator(path_to_watch)) {
            files[file.path().string()] = std::make_pair(std::filesystem::last_write_time(file), file.status().type());
        }
    } catch (std::filesystem::filesystem_error& error) {
        std::cerr << error.what() << std::endl;
    }
    watcher = std::thread(&FileWatcher::StartWatch, this);
}


FileSynchronizer::FileWatcher::~FileWatcher() {
    if (watcher.joinable()) {
        watcher.join();
    }
}

void FileSynchronizer::FileWatcher::StartWatch() {
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
                if(files.find(file.path().string()) != files.end()) {
                    continue;
                }
                files[file.path().string()] = std::make_pair(std::filesystem::last_write_time(file), file.status().type());
                UpdateFile(files.find(file.path().string()), FileStatus::Created);
            }

            // Notify
            if (!changed_files.empty() && working) {
                PauseWatching();
                if (mediator) {
                    mediator->Notify(EventType::FileChanged);
                } else {
                    ContinueWatching();
                }
            }
        }
    }
}

void FileSynchronizer::FileWatcher::StartWatching() {
    if (!working) {
        watcher = std::thread(&FileWatcher::StartWatch, this);
    }
}

void FileSynchronizer::FileWatcher::StopWatching() {
    working = false;
}

void FileSynchronizer::FileWatcher::PauseWatching() {
    watching = false;
}

void FileSynchronizer::FileWatcher::ContinueWatching() {
    changed_files.clear();
    watching = true;
}
