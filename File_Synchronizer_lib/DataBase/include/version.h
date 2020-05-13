#ifndef FILE_SYNCHRONIZER_VERSION_H
#define FILE_SYNCHRONIZER_VERSION_H

#include "file.h"

class Version {
private:
    int id;
    File target;
    std::string hash;
public:
    virtual ~Version() = default;

    void SetId(const int& version_id);
    int GetId();
    void SetTarget(const File& file);
    File GetTarget();
    void SetHash(const std::string& _filename);
    std::string GetFilename();
};


#endif //FILE_SYNCHRONIZER_VERSION_H
