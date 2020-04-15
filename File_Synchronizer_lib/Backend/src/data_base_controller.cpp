//
// Created by arugaf on 15.04.2020.
//

#include "data_base_controller.h"

using FileSynchronizer::DataBaseController;

FileSynchronizer::DataBaseController::DataBaseController(const fs::directory_entry& path_to_files,
                                                         std::shared_ptr<DataBase> data_base,
                                                         std::shared_ptr<Controller> controller,
                                                         fs::path configure_file_path,
                                                         std::shared_ptr<LocalData> data) {

}

void FileSynchronizer::DataBaseController::Watch() {

}

int FileSynchronizer::DataBaseController::RemoveFileHandler(std::wstring file_name) {
    return 0;
}

int FileSynchronizer::DataBaseController::ChangeFileHandler(std::wstring file_name) {
    return 0;
}

int FileSynchronizer::DataBaseController::MoveFileHandler(std::wstring file_name, fs::path new_path) {
    return 0;
}

int FileSynchronizer::DataBaseController::RenameFileHandler(std::wstring file_name, std::wstring new_file_name) {
    return 0;
}
