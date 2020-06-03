#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONMANAGER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONMANAGER_H_

#include <vector>
#include <filesystem>

class IVersionManager {
public:
    virtual ~IVersionManager() = default;

    virtual void RestoreFileFromVersion(const std::filesystem::path &filename, const int &number) = 0;
    virtual std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::filesystem::path &filename) = 0;
    virtual std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::filesystem::path &filename, const int &number) = 0;
    virtual int DeleteVersion(const std::filesystem::path &file, const std::filesystem::path &version) = 0;
    virtual void DeleteFile(const std::filesystem::path &file) = 0;
    virtual void RestoreFile(const std::filesystem::path &file) = 0;
    virtual int DeleteFileInstantly(const std::filesystem::path &file) = 0;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONMANAGER_H_
