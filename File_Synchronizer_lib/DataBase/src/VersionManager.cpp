#include "VersionManager.h"

VersionManager::VersionManager(const std::filesystem::path &_source, VersionCreator *_versionCreator)  {
    SetVersionsPath(_source);
    versionCreator = _versionCreator;
}

VersionManager::~VersionManager() {
    delete versionCreator;
    versionCreator = nullptr;
}

void VersionManager::SetVersionsPath(const std::filesystem::path& source) {
    versionsPath = source / "versions";
    std::filesystem::create_directory(versionsPath);
}

void VersionManager::CreateIndex(const std::filesystem::path &file) {
    std::filesystem::path index = versionCreator->AddToIndex(file, versionsPath);
}

void VersionManager::CreateVersion(const std::filesystem::path& file) {
    std::filesystem::path versionPath =  versionCreator->CreateVersion(file, versionsPath);
    CreateIndex(file);
}

void VersionManager::CreateDiff(const std::filesystem::path &file) {
    versionCreator->CreateDiff(file, versionsPath);
}

int VersionManager::DeleteVersion(const std::filesystem::path& file, const std::filesystem::path& version) {
    std::filesystem::path pathToVersionForDelete = versionsPath / file.stem() / version;

    int success = std::filesystem::remove_all(pathToVersionForDelete);
    return success;
}

void VersionManager::DeleteFile(const std::filesystem::path &file) {
    std::filesystem::path pathForDelete = versionsPath / file.stem();

    std::filesystem::permissions(pathForDelete, std::filesystem::perms::owner_read | std::filesystem::perms::group_read
    | std::filesystem::perms::others_read, std::filesystem::perm_options::replace);
}

void VersionManager::RestoreFile(const std::filesystem::path &file) {
    std::filesystem::path pathForDelete = versionsPath / file.stem();

    std::filesystem::permissions(pathForDelete, std::filesystem::perms::owner_all | std::filesystem::perms::group_all
    | std::filesystem::perms::others_read | std::filesystem::perms::others_write, std::filesystem::perm_options::replace);
}

int VersionManager::DeleteFileInstantly(const std::filesystem::path &file) {
    std::filesystem::path pathForDelete = versionsPath / file.stem();

    std::function checkPerms = [&](std::filesystem::perms p) {
        bool isClose = false;

        if ((p & std::filesystem::perms::owner_all) == std::filesystem::perms::owner_read ||
            (p & std::filesystem::perms::group_all) == std::filesystem::perms::group_read) {
            isClose = true;
        }

        return isClose;
    };

    if ( checkPerms(std::filesystem::status(pathForDelete).permissions()) ) {
        RestoreFile(file);
    }

    int success = std::filesystem::remove_all(pathForDelete);
    return success;
}

void VersionManager::RestoreFileFromVersion(const std::filesystem::path &filename, const int &number) {
    std::vector<std::filesystem::path> finded = GetVersionHistoryForFile(filename, number);
    std::filesystem::copy_file(finded[0], filename, std::filesystem::copy_options::overwrite_existing);

    CreateIndex(filename);
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




