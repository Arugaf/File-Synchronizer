#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONCREATOR_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONCREATOR_H_

#include <filesystem>

class IVersionCreator {
    virtual void CreateIndex(const std::filesystem::path& file) = 0;
    virtual void CreateVersion(const std::filesystem::path &file) = 0;
    virtual void CreateDiff(const std::filesystem::path &file) = 0;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_INCLUDE_IVERSIONCREATOR_H_
