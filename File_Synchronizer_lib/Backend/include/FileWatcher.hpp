#ifndef FILE_SYNCHRONIZER_FILEWATCHER_HPP
#define FILE_SYNCHRONIZER_FILEWATCHER_HPP

#include "IMediator.h"

#include <chrono>
#include <exception>
#include <filesystem>
#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace FileSynchronizer {
    enum class FileStatus {
        Changed,
        Created,
        Deleted
    };

    namespace FileWatcherException {
        class Exception : public std::runtime_error {
        public:
            explicit
            Exception(const std::string& msg) : std::runtime_error(msg) {};
        };

        class InvalidPath : public Exception {
        public:
            InvalidPath() : Exception("Invalid path") {};
            explicit
            InvalidPath(const std::string& path) : Exception("Invalid path: " + path) {};
        };
    }

    // TODO: Игнорировать скрытые файлы
    // TODO: Стоит ли переделать в синглтон, чтобы нельзя было запускать дважды? Или другой способ решения, чтобы можно было отслеживать несколько директорий за раз?
    class FileWatcher {
    public:
        // TODO: Константная ссылка или мув?
        explicit
        FileWatcher(std::string path_to_watch,
                    int ms_delay = default_delay);
        FileWatcher(std::string path_to_watch,
                    std::unordered_set<std::string> ignored_files,
                    int ms_delay = default_delay);
        FileWatcher(std::string path_to_watch,
                    std::unordered_map<std::string,
                                       std::pair<std::filesystem::file_time_type,
                                       std::filesystem::file_type>> previous_files,
                    int ms_delay = default_delay);
        FileWatcher(std::string path_to_watch,
                    std::unordered_set<std::string> ignored_files,
                    std::unordered_map<std::string,
                                       std::pair<std::filesystem::file_time_type,
                                       std::filesystem::file_type>> previous_files,
                    int ms_delay = default_delay);
        ~FileWatcher();

        std::unordered_map<std::string, FileStatus> GetChangedFiles() const;

        // TODO: Как избавиться от сырого указателя и стоит ли кидать указатель в конструктор для организации нормальной композиции вместо текущей dependency injection?
        void StartWatching(IMediator* new_mediator);
        void StopWatching();
        void PauseWatching();
        void ContinueWatching();

        void UpdateFile(const std::string& relative_path);

        bool IsWorking() const;
        bool IsWatching() const;
        bool IsActive() const {
            return watcher.joinable();
        }

    private:
        static const int default_delay = 3e3;

        std::string path_to_watch;
        std::chrono::milliseconds delay;
        std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, std::filesystem::file_type>> files;
        std::unordered_set<std::string> ignored_files;

        bool mutable working = false;
        bool mutable watching = true;
        std::thread watcher;
        std::unordered_map<std::string, FileStatus> mutable changed_files;

        IMediator* mediator;

        void Watch();

        bool IsIgnored(const std::string& file) const;

        template<typename T>
        bool IsExisting(const T& file) const {
            return std::filesystem::exists(file->first);
        };

        template<typename T>
        bool IsRegular(const T& file) const {
            return file->second.second == std::filesystem::file_type::regular;
        };

        template<typename T>
        bool IsChanged(const T& file) const {
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
