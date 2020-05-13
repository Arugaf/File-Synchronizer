#ifndef FILE_SYNCHRONIZER_VERSIONCREATOR_H
#define FILE_SYNCHRONIZER_VERSIONCREATOR_H

#include "file.h"
#include "version.h"

class IVersionCreator {
public:
    virtual void AddToIndex() {};
    virtual void CreateDiff() {};
};

class VersionCreator : public IVersionCreator {
private:
    std::string ComputeMD5();
public:
    void AddToIndex(File file, const std::filesystem::path& versionsDirectory);
    void CreateDiff(File file);
};

#endif //FILE_SYNCHRONIZER_VERSIONCREATOR_H
