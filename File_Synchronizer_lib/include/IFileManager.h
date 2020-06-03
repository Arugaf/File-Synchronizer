#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IFILEMANAGER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IFILEMANAGER_H_

#include <filesystem>
#include <unordered_map>
#include <utility>

class IFileManager {
public:
    virtual ~IFileManager() = default;

    virtual std::pair<std::filesystem::path, std::filesystem::file_time_type> GetFileInfo(const std::filesystem::path& file) = 0;

    typedef std::unordered_map<std::filesystem::path, std::filesystem::file_time_type, std::hash<std::string>> list;
    virtual list GetInfo() = 0;

    virtual void DeleteFile(const std::filesystem::path& file) = 0;
    virtual void SetFileInfo(const std::filesystem::path& file) = 0;
    virtual void Clear() = 0;
    virtual void Load() = 0;
    virtual void Save() = 0;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IFILEMANAGER_H_
