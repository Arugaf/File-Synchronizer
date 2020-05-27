#ifndef FILE_SYNCHRONIZER_FILEWATCHER_HPP
#define FILE_SYNCHRONIZER_FILEWATCHER_HPP

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
    typedef std::unordered_map<std::string, FileStat> FilesInfo;
    typedef std::unordered_map<std::string, FileStatus> FileStatuses;
    // TODO: Игнорировать скрытые файлы
    // TODO: Стоит ли переделать в синглтон, чтобы нельзя было запускать дважды? Или другой способ решения, чтобы можно было отслеживать несколько директорий за раз?
    class FileWatcher {
    public:
        // TODO: Константная ссылка или мув?
        explicit FileWatcher(std::string path_to_watch, int ms_delay = default_delay);
        FileWatcher(std::string path_to_watch, FileNames ignored_files, int ms_delay);
        FileWatcher(std::string path_to_watch, FilesInfo previous_files, int ms_delay = default_delay);
        FileWatcher(std::string path_to_watch, FileNames ignored_files,
                    FilesInfo previous_files, int ms_delay = default_delay);
        ~FileWatcher();

        FileStatuses GetChangedFiles() const;

        // TODO: Как избавиться от сырого указателя и стоит ли кидать указатель в конструктор для организации нормальной композиции вместо текущей dependency injection?
        void StartWatching(IMediator* new_mediator);
        void StopWatching();

        void PauseWatching();
        void ContinueWatching();

        //void UpdateFile(const std::string& relative_path);

        bool IsWorking() const;
        bool IsWatching() const;
        bool IsActive() const;

    private:
        static const int default_delay = 1e4;

        std::string path_to_watch;
        std::chrono::milliseconds delay;
        FilesInfo files;
        FileNames ignored_files;

        bool working = false;
        bool watching = true;
        std::thread watcher;
        std::unordered_map<std::string, FileStatus> changed_files;

        IMediator* mediator;

        void Watch();
        bool IsIgnored(const std::string& file) const;
        template<typename T>
        bool IsExisting(const std::iterator<FilesInfo>& file) const {
            return std::filesystem::exists(file->first);
        };

        template<typename T>
        bool IsRegular(const T& file) const {
            return file->second.file_type == std::filesystem::file_type::regular;
        };

        template<typename T>
        bool IsChanged(const T& file) const {
            return std::filesystem::last_write_time(file->first) != file->second.last_modify_time;
        };

        template<typename T>
        void UpdateFile(T&& file, FileStatus status) {
            if (IsRegular(file)) {
                changed_files[std::filesystem::path(file->first).lexically_relative(path_to_watch)] = status;
            }

            switch (status) {
                case (FileStatus::Changed): {
                    file->second.last_modify_time = std::filesystem::last_write_time(file->first);
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
