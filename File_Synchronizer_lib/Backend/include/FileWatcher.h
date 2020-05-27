#ifndef FILE_SYNCHRONIZER_FILEWATCHER_H
#define FILE_SYNCHRONIZER_FILEWATCHER_H

#include "FileNames.h"
#include "FileStat.h"
#include "FileStatus.h"
#include "FileWatcherException.h"
#include "IMediator.h"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include <utility>

namespace FileSynchronizer {
    namespace fs = std::filesystem;

    typedef std::unordered_map<std::string, FileStat> FilesInfo;
    typedef std::unordered_map<std::string, FileStatus> FileStatuses;
    typedef std::unordered_set<std::string> path_list;

    class FileWatcher {
    public:
        explicit FileWatcher(path_list paths_to_watch, int ms_delay = default_delay);
        FileWatcher(path_list paths_to_watch, FileNames ignored_files, int ms_delay = default_delay);
        FileWatcher(path_list paths_to_watch, FilesInfo previous_files, int ms_delay = default_delay);
        FileWatcher(path_list paths_to_watch, FileNames ignored_files,
                    FilesInfo previous_files, int ms_delay = default_delay);

        FileWatcher(const FileWatcher& other) = delete;
        FileWatcher(FileWatcher&& other) = delete;

        FileWatcher& operator=(const FileWatcher& other) = delete;
        FileWatcher& operator=(FileWatcher&& other) = delete;

        ~FileWatcher();

        FileStatuses GetChangedFiles() const;

        void StartWatching(const std::shared_ptr<IMediator>& new_mediator);
        void StopWatching();

        void PauseWatching();
        void ContinueWatching();

        bool IsWorking() const;
        bool IsWatching() const;
        bool IsActive() const;

    private:
        static const int default_delay = 1e3;
        std::chrono::milliseconds delay;

        path_list paths_to_watch;
        FilesInfo files;
        FileNames ignored_files;
        FileStatuses changed_files;

        bool working = false;
        bool watching = true;
        std::thread watcher;
        std::shared_ptr<IMediator> mediator;

        void Watch();

        bool IsIgnored(const std::string& file) const;

        template<typename T>
        bool IsExisting(const T& file) const;

        template<typename T>
        bool IsRegular(const T& file) const;

        template<typename T>
        bool IsChanged(const T& file) const;

        template<typename T>
        void UpdateFile(T&& file, FileStatus status);
    };
}

#include "FileWatcher.hpp"

#endif //FILE_SYNCHRONIZER_FILEWATCHER_H
