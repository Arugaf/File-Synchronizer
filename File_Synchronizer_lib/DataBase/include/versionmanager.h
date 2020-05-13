#ifndef FILE_SYNCHRONIZER_VERSIONMANAGER_H
#define FILE_SYNCHRONIZER_VERSIONMANAGER_H

#include <stack>
#include <filesystem>

#include "version.h"
#include "transactionjournal.h"
#include "versioncreator.h"

class VersionManager {
private:
    std::filesystem::path versionsPath;
    std::stack<Version> history;
    ITransactionJournal* logger;
    IVersionCreator* versionCreator;
public:
    VersionManager(): logger(new TransactionJournal()), versionCreator(new VersionCreator()) {};
    VersionManager(ITransactionJournal* _logger, IVersionCreator* _versionCreator) {
        logger = _logger;
        versionCreator = _versionCreator;
    };

    void SetVersionsPath(const std::filesystem::path& source);
    std::filesystem::path GetVersionsPath();
    void CreateVersion();
    void DeleteVersion(const Version&);
    std::stack<Version> GetVersionHistoryForFile(const std::string& filename);
};


#endif //FILE_SYNCHRONIZER_VERSIONMANAGER_H
