#include "VersionManager.h"

void VersionManager::SetVersionsPath(const std::filesystem::path& source) {
    versionsPath = source / "versions";
}

void VersionManager::CreateIndex(const std::filesystem::path &file) {
    std::filesystem::path index = versionCreator->AddToIndex(file, versionsPath);
}

void VersionManager::CreateVersion(const std::filesystem::path& file) {
    std::filesystem::path versionPath =  versionCreator->CreateVersion(file, versionsPath);
    CreateIndex(file);
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

std::vector<std::filesystem::path> VersionManager::GetVersionHistoryForFile(const std::filesystem::path& filename) {
    namespace fs = std::filesystem;
    fs::path source = versionsPath / filename.stem();
    history.clear();

    for (auto& item: std::filesystem::directory_iterator(source) ) {
        if (item.path().stem() != "index") {
            history.push_back(item);
        }
    }

    std::sort(history.begin(), history.end(), [](const fs::path& l, const fs::path& r) {
        return (fs::last_write_time(l) < fs::last_write_time(r));
    });

    return history;
}

std::vector<std::filesystem::path> VersionManager::GetVersionHistoryForFile(const std::filesystem::path& filename, const int& number) {
    std::vector<std::filesystem::path> tmp = GetVersionHistoryForFile(filename);
    std::vector<std::filesystem::path> finded;

    if (number >= tmp.size()) {
        finded.push_back(history.back());
    } else {
        finded.push_back(history[number]);
    }

    return finded;
}


std::filesystem::path VersionManager::CreateDiff(const std::filesystem::path &file) {
    versionCreator->CreateDiff(file, versionsPath);
}


