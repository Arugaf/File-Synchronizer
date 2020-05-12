//
// Created by arugaf on 11.05.2020.
//

#ifndef FILE_SYNCHRONIZER_FILEWATCHER_HPP
#define FILE_SYNCHRONIZER_FILEWATCHER_HPP

#include "IMediator.h"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include <utility>
#include <vector>

namespace FileSynchronizer {
    enum class FileStatus {
        Changed,
        Created,
        Deleted
    };

    class FileWatcher {
    public:
        FileWatcher(const std::string& path_to_watch, std::shared_ptr<IMediator> mediator, int ms_delay = 3e5);
        ~FileWatcher();

        void StartWatching();
        void StopWatching();
        void PauseWatching();
        void ContinueWatching();

    private:
        std::string path_to_watch;
        std::chrono::milliseconds delay;
        std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, std::filesystem::file_type>> files;

        bool mutable working = true;
        bool mutable watching = true;
        std::thread watcher;
        std::unordered_map<std::string, FileStatus> mutable changed_files;

        std::shared_ptr<IMediator> mediator;

        void StartWatch();

        template<typename T>
        bool IsExisting(const T& file) {
            return std::filesystem::exists(file->first);
        };

        template<typename T>
        bool IsRegular(const T& file) {
            return file->second.second == std::filesystem::file_type::regular;
        };

        template<typename T>
        bool IsChanged(const T& file) {
            return std::filesystem::last_write_time(file->first) != file->second.first;
        };

        template<typename T>
        void UpdateFile(T&& file, FileStatus status) {
            if (IsRegular(file)) {
                changed_files[std::filesystem::path(file->first).lexically_relative(path_to_watch)] = status;
            }

            switch(status) {
                case (FileStatus::Changed): {
                    file->second.first = std::filesystem::last_write_time(file->first);
                    break;
                }

                case (FileStatus::Deleted): {
                    file = files.erase(file);
                    break;
                }

                default: {
                    break;
                }
            }
        };
    };
}

#endif //FILE_SYNCHRONIZER_FILEWATCHER_HPP
