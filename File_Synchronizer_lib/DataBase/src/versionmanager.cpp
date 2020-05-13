#include "versionmanager.h"

void VersionManager::SetVersionsPath(const std::filesystem::path& source) {
    versionsPath = source;
}

std::filesystem::path VersionManager::GetVersionsPath() {
    return versionsPath;
}

void VersionManager::CreateVersion() {

}

void VersionManager::DeleteVersion(const Version &) {

}

std::stack<Version> VersionManager::GetVersionHistoryForFile(const std::string& filename) {
    return std::stack<Version>();
}
