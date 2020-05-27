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
    manager->Load();
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
