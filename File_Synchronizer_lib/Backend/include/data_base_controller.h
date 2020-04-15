//
// Created by arugaf on 15.04.2020.
//

#ifndef FILE_SYNCHRONIZER_DATA_BASE_CONTROLLER_H
#define FILE_SYNCHRONIZER_DATA_BASE_CONTROLLER_H

#include <filesystem>
#include <memory>
#include <vector>

#include <sys/inotify.h>

// Следит за изменениями в файловой системе, меняет бд и оповещает основной контроллер в случае появления таковых.

namespace fs = std::filesystem;

class DataBase;
class Controller;
class LocalData;

namespace FileSynchronizer {
    class DataBaseController {
    public:
        DataBaseController(const fs::directory_entry& path_to_files, std::shared_ptr<DataBase> data_base,
                           std::shared_ptr<Controller> controller, fs::path configure_file_path,
                           std::shared_ptr<LocalData> data);

        void Watch();

    private:
        int RemoveFileHandler(std::wstring file_name);
        int ChangeFileHandler(std::wstring file_name);
        int MoveFileHandler(std::wstring file_name, fs::path new_path);
        int RenameFileHandler(std::wstring file_name, std::wstring new_file_name);

        std::shared_ptr<DataBase> data_base;
        std::shared_ptr<Controller> controller;

        std::vector<int> inotify_descriptors;

        std::shared_ptr<LocalData> local_data;
    };
} // FileSynchronizer namespace end

#endif //FILE_SYNCHRONIZER_DATA_BASE_CONTROLLER_H
