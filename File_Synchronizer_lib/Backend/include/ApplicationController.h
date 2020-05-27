#ifndef FILE_SYNCHRONIZER_APPLICATIONCONTROLLER_H
#define FILE_SYNCHRONIZER_APPLICATIONCONTROLLER_H

#include "DataBaseController.h"
#include "VersionManagerWrapper.h"

#include <filesystem>

namespace FileSynchronizer {

    // TODO: Версии

    namespace fs = std::filesystem;

    class ApplicationController {
    public:
        explicit ApplicationController(const fs::path& working_path, DataBaseController& controller, DataBaseWrapper& DB, VersionManagerWrapper& VM);

        void Start();
        void Stop();

        void AddDirectory(const fs::path& dir);
        void DeleteDirectory(const fs::path& dir);

        void AddIgnoredFile(const fs::path& file);
        void DeleteIgnoredFile(const fs::path& file);

        void ShowFilesList();

        void ShowFileVersions(const fs::path& file);
        void RestoreVersion(const fs::path& file, int index);

        void ShowLog();
        void ShowLogHead(int count = 5);
        void ShowLogTail(int count = 5);
        void ShowLogData(const std::string& date);
        void ShowLogFile(const std::string& file);

        void ClearDB();

    private:
        DataBaseController& controller;
        DataBaseWrapper& DB;
        VersionManagerWrapper& VM;
        fs::path config_file;

        std::thread listener;
        bool working = true;

        void Listen();
    };
}

#endif //FILE_SYNCHRONIZER_APPLICATIONCONTROLLER_H
