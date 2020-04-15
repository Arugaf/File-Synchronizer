//
// Created by arugaf on 15.04.2020.
//

#ifndef FILE_SYNCHRONIZER_LOCAL_DATA_H
#define FILE_SYNCHRONIZER_LOCAL_DATA_H

#include <filesystem>

namespace fs = std::filesystem;

namespace FileSynchronizer {
    class LocalData {
    public:
        explicit LocalData(fs::path configure_file_path);

        auto GetID();
        auto GetUserName();
        auto GetConfigureFilePath();
        auto GetCurrentTransaction();

    private:
        int id;
        int current_transaction;
        std::wstring user_name;
        fs::path configure_file_path;
    };
} // FileSynchronizer namespace end


#endif //FILE_SYNCHRONIZER_LOCAL_DATA_H
