#ifndef FILE_SYNCHRONIZER_VERSIONMANAGER_H
#define FILE_SYNCHRONIZER_VERSIONMANAGER_H

#include <vector>
#include <map>
#include <stack>
#include <filesystem>

#include "transactionjournal.h"
#include "versioncreator.h"


class VersionManager {
private:
    std::filesystem::path versionsPath;
    std::vector<std::filesystem::path> history;
    ITransactionJournal* logger;
    VersionCreator* versionCreator;
public:
    VersionManager(): logger(new TransactionJournal()), versionCreator(new VersionCreator()) {};
    VersionManager(ITransactionJournal* _logger): versionCreator(new VersionCreator()) {
        logger = _logger;
    };
    VersionManager(ITransactionJournal* _logger, VersionCreator* _versionCreator) {
        logger = _logger;
        versionCreator = _versionCreator;
    };

    void SetVersionsPath(const std::filesystem::path& source);
    std::filesystem::path GetVersionsPath();
    void CreateVersion(File file);
    void DeleteVersion(const std::string& filename, const std::string& version);
    std::vector<std::filesystem::path> GetVersionHistoryForFile(const std::string& filename, std::ostream &out);
};

#endif //FILE_SYNCHRONIZER_VERSIONMANAGER_H
