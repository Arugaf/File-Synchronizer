#include "versionmanager.h"

void VersionManager::set_versions_path(const fs::path &source) {

}

fs::path VersionManager::get_versions_path() {
    return fs::path();
}

void VersionManager::CreateVersion() {

}

void VersionManager::DeleteVersion(const Version &) {

}

std::stack<Version> VersionManager::GetVersionHistoryForFile(const std::string& filename) {
    return std::stack<Version>();
}
