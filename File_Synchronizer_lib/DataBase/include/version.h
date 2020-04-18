#ifndef FILE_SYNCHRONIZER_VERSION_H
#define FILE_SYNCHRONIZER_VERSION_H

#include "file.h"

class Version {
private:
    int id;
    File *target;
    std::string version_filename;
public:
    void set_id(const int& version_id);
    int get_id();
    void set_target(const File& file);
    File get_target();
    void set_version_filename(const std::string& filename);
    std::string get_version_filename();
};


#endif //FILE_SYNCHRONIZER_VERSION_H
