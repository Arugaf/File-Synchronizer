#include "DataBaseWrapper.h"

using FileSynchronizer::DataBaseWrapper;

DataBaseWrapper::DataBaseWrapper(std::unique_ptr<IFileManager> manager) : manager(std::move(manager)) {

}

void DataBaseWrapper::HandleFileCreation(const std::filesystem::path& file) {
    manager->SetFileInfo(file);
}

void DataBaseWrapper::HandleFileModification(const std::filesystem::path& file) {
    manager->SetFileInfo(file);
}

void DataBaseWrapper::HandleFileDeletion(const std::filesystem::path& file) {
    manager->DeleteFile(file);
}

void DataBaseWrapper::ClearDB() {
    manager->Clear();
}

void DataBaseWrapper::LoadDBFromFile() {
    // manager->Load();
}

void DataBaseWrapper::SaveDbToFile() {
    manager->Save();
}

std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>>
DataBaseWrapper::GetAllFiles() {
    return manager->GetInfo();
};

std::pair<std::filesystem::path, std::filesystem::file_time_type> FileSynchronizer::DataBaseWrapper::GetFileInfo(const fs::path& file) {
    return manager->GetFileInfo(file);
}

#ifndef DATABASE

class FileManager : public IFileManager {
public:
    std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const std::filesystem::path& file) override {
        return std::make_pair("test_path", std::filesystem::file_time_type(std::chrono::seconds(5)));
    };
    std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> GetInfo() override {
        std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> files;
        files["abc"] = std::filesystem::file_time_type(std::chrono::seconds(5));
        return files;
    };
    void DeleteFile(const std::filesystem::path&) override {

    };
    void SetFileInfo(const std::filesystem::path&) override {

    };
    void Clear() override {

    };
    void Load() override {

    };
    void Save() override {

    };
    ~FileManager() override = default;
};

/*FileSynchronizer::DataBaseWrapper::DataBaseWrapper() {
    manager = std::make_unique<FileManager>();
}*/

#endif
