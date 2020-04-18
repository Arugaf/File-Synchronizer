#ifndef FILE_SYNCHRONIZER_VERSIONCREATOR_H
#define FILE_SYNCHRONIZER_VERSIONCREATOR_H

#include "file.h"
#include "version.h"

class IVersionCreator {
public:
    virtual void AddToIndex(const File&) = 0;
    virtual void CreateDiff(const File&) = 0;
};

class VersionCreator : public IVersionCreator {
    void AddToIndex(const File& file) override;
    void CreateDiff(const File& file) override;
};

#endif //FILE_SYNCHRONIZER_VERSIONCREATOR_H
