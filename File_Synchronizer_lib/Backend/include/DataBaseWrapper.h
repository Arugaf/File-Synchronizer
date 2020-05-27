#ifndef FILE_SYNCHRONIZER_DATABASEWRAPPER_H
#define FILE_SYNCHRONIZER_DATABASEWRAPPER_H

#include "IFileManager.h"

#include <filesystem>
#include <memory>
#include <unordered_map>

namespace FileSynchronizer {
    namespace fs = std::filesystem;

    class DataBaseWrapper {
    public:
#ifndef DATABASE
        DataBaseWrapper();
#endif
        explicit DataBaseWrapper(std::unique_ptr<IFileManager>);

        void HandleFileCreation(const fs::path& file);
        void HandleFileModification(const fs::path& file);
        void HandleFileDeletion(const fs::path& file);

        void ClearDB();
        void LoadDBFromFile();
        void SaveDbToFile();

        std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> GetAllFiles();
        std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const fs::path& file);

    private:
        std::unique_ptr<IFileManager> manager;
    };
}

#endif //FILE_SYNCHRONIZER_DATABASEWRAPPER_H
