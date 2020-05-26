#include "versionmanager.h"

void VersionManager::SetVersionsPath(const std::filesystem::path& source) {
    versionsPath = source;
}

std::filesystem::path VersionManager::GetVersionsPath() {
    return versionsPath;
}

void VersionManager::CreateVersion(const std::filesystem::path& file) {
    std::filesystem::path versionPath =  versionCreator->CreateVersion(file, versionsPath);
    std::filesystem::path index = versionCreator->AddToIndex(file, versionsPath);
}

int VersionManager::DeleteVersion(const std::filesystem::path& file, const std::string& version) {
    std::filesystem::path pathToVersionForDelete = versionsPath / file.stem() / version;

    int success = std::filesystem::remove_all(pathToVersionForDelete);
    return success;
}

int VersionManager::DeleteFile(const std::string &filename) {
    std::filesystem::path pathForDelete = versionsPath / filename;

    int success = std::filesystem::remove_all(pathForDelete);
    return success;
}

std::vector<std::filesystem::path> VersionManager::GetVersionHistoryForFile(const std::string& filename, const std::string& number) {
    namespace fs = std::filesystem;
    fs::path source = versionsPath / filename;
    history.clear();

    for (auto& item: std::filesystem::directory_iterator(source) ) {
        if (item.path().stem() != "index") {
            history.push_back(item);
        }
    }

    std::sort(history.begin(), history.end(), [](const fs::path& l, const fs::path& r) {
        return (fs::last_write_time(l) < fs::last_write_time(r));
    });

    if (number == "*") {
        return history;
    } else {
        std::vector<std::filesystem::path> tmp;
        if (number == "last" || std::stoi(number) >= history.size() || std::stoi(number) < 0) {
            tmp.push_back(history.back());
        } else {
            tmp.push_back(history[std::stoi(number)]);
        }

        return tmp;
    }
}

