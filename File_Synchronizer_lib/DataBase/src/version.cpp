#include "version.h"

void Version::SetId(const int &version_id) {
    id = version_id;
}

int Version::GetId() {
    return id;
}

void Version::SetTarget(const File &file) {
    target = file;
}

File Version::GetTarget() {
    return target;
}

void Version::SetHash(const std::string &_hash) {
    hash = _hash;
}

std::string Version::GetFilename() {
    return hash;
}
