#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONMANAGER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONMANAGER_H_

#include <vector>
#include <filesystem>

class IVersionManager {
public:
    virtual ~IVersionManager() = default;

    virtual std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::filesystem::path &filename) = 0;
    virtual std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::filesystem::path &filename, const int &number) = 0;
};

class IVersionCreator {
    virtual void CreateIndex(const std::filesystem::path& file) = 0;
    virtual void CreateVersion(const std::filesystem::path &file) = 0;
    virtual std::filesystem::path CreateDiff(const std::filesystem::path &file) = 0;
    virtual int DeleteVersion(const std::filesystem::path &file, const std::string &version) = 0;
    virtual int DeleteFile(const std::string &filename) = 0;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONMANAGER_H_
