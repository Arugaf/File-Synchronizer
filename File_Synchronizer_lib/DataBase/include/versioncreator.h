#ifndef FILE_SYNCHRONIZER_VERSIONCREATOR_H
#define FILE_SYNCHRONIZER_VERSIONCREATOR_H

#include "file.h"
#include "version.h"

class VersionCreator{
private:
    std::string ComputeHashSum(const std::filesystem::path& targetSource);
public:
    virtual ~VersionCreator() = default;

    std::filesystem::path AddToIndex(File file, const std::filesystem::path& versionsDirectory);
    std::filesystem::path CreateDiff(File file, const std::filesystem::path& versionsDirectory);
};

#include <vector>
#include <functional>
#include <fstream>

#include "versioncreator.h"

#endif //FILE_SYNCHRONIZER_VERSIONCREATOR_H
