#include "versionmanager.h"

void VersionManager::SetVersionsPath(const std::filesystem::path& source) {
    versionsPath = source;
}

std::filesystem::path VersionManager::GetVersionsPath() {
    return versionsPath;
}

void VersionManager::CreateVersion(const File& file) {
    std::filesystem::path versionPath =  versionCreator->CreateDiff(file, versionsPath);
    std::filesystem::path index = versionCreator->AddToIndex(file, versionsPath);

    history.push_back(versionPath);

    Transaction versionTransaction(Operation::created, versionPath, 1);
    versionTransaction.FormMessage();
    Transaction indexTransaction(Operation::created, index, 1);
    indexTransaction.FormMessage();
    logger->AddTransaction(versionTransaction);
    logger->AddTransaction(indexTransaction);

}

void VersionManager::DeleteVersion(const std::string& filename, const std::string& version) {
    std::filesystem::path pathToVersionForDelete = versionsPath / filename / version;

    if (!std::filesystem::exists(version)) {
        return;
    } else {
        int success = 0;
        try {
            success = std::filesystem::remove_all(pathToVersionForDelete);

        } catch (std::filesystem::filesystem_error& exception) {
            throw exception;
        }
    }
}

std::vector<std::filesystem::path> VersionManager::GetVersionHistoryForFile(const std::string& filename, std::ostream &out) {
    namespace fs = std::filesystem;
    fs::path source = versionsPath / filename;

    for (auto& item: std::filesystem::directory_iterator(source) ) {
        history.push_back(item);
    }

    std::sort(history.begin(), history.end(), [](const fs::path& l, const fs::path& r) {
      return (fs::last_write_time(l) < fs::last_write_time(r));
    });

    for (auto& item: history) {
        out << item << std::endl;
    }

    return history;
}
