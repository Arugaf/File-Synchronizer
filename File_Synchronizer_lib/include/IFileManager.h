#ifndef FILE_SYNCHRONIZER_IFILEMANAGER_H
#define FILE_SYNCHRONIZER_IFILEMANAGER_H

#include <filesystem>
#include <unordered_map>

// Интерфейс другой части

class IFileManager {
public:
    virtual std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const std::filesystem::path& file) = 0;
    virtual std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> GetInfo() = 0;
    virtual void DeleteFile(const std::filesystem::path&) = 0;
    virtual void SetFileInfo(const std::filesystem::path&) = 0;
    virtual void Clear() = 0;
    virtual void Load() = 0;
    virtual void Save() = 0;
    virtual ~IFileManager() = default;
};

#endif //FILE_SYNCHRONIZER_IFILEMANAGER_H
