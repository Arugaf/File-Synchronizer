#ifndef FILE_SYNCHRONIZER_VERSION_H
#define FILE_SYNCHRONIZER_VERSION_H

#include "file.h"

class Version {
private:
    std::filesystem::path targetFilepath;
    std::string hash;
public:
    Version() = default;
    Version(std::filesystem::path _target, std::string _hash): targetFilepath(std::move(_target)),
                                                               hash(std::move(_hash)) {};
    virtual ~Version() = default;

    void SetTarget(File file);
    std::filesystem::path GetTarget();
    void SetHash(const std::string& _filename);
    std::string GetFilename();
};


#endif //FILE_SYNCHRONIZER_VERSION_H
