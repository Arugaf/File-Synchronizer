#include "version.h"

void Version::SetTarget(File file) {
    targetFilepath = file.GetFilepath();
}

std::filesystem::path Version::GetTarget() {
    return targetFilepath;
}

void Version::SetHash(const std::string &_hash) {
    hash = _hash;
}

std::string Version::GetFilename() {
    return hash;
}

