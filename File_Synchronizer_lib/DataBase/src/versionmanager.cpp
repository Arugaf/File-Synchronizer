#include "versionmanager.h"

void VersionManager::SetVersionsPath(const std::filesystem::path& source) {
    versionsPath = source;
}

std::filesystem::path VersionManager::GetVersionsPath() {
    return versionsPath;
}

void VersionManager::CreateVersion(File file) {
    std::filesystem::path versionPath =  versionCreator->CreateDiff(file.GetFilepath(), versionsPath);
    std::filesystem::path index = versionCreator->AddToIndex(file.GetFilepath(), versionsPath);

    // TODO: map <file, history>?
    history.push_back(versionPath);

    Transaction versionTransaction(Operation::created, versionPath, 1);
    versionTransaction.FormMessage();
    Transaction indexTransaction(Operation::created, index, 1);
    indexTransaction.FormMessage();
    logger->AddTransaction(versionTransaction);
    logger->AddTransaction(indexTransaction);

}

int VersionManager::DeleteVersion(const std::filesystem::path& file, const std::string& version) {
    std::filesystem::path pathToVersionForDelete = versionsPath / file.stem() / version;

    int success = 0;
    success = std::filesystem::remove_all(pathToVersionForDelete);

    if (success != 0) {
        Transaction deleteTransaction(Operation::deleted, pathToVersionForDelete, 1);
        logger->AddTransaction(deleteTransaction);
    }

    return success;
}

#include <iostream>

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
        return reinterpret_cast<const std::vector<std::filesystem::path> &>(history[std::stoi(number)]);
    }
}
