#ifndef FILE_SYNCHRONIZER_VERSIONMANAGER_H
#define FILE_SYNCHRONIZER_VERSIONMANAGER_H

#include <stack>
#include <filesystem>
namespace fs = std::filesystem;

#include "version.h"
#include "logger.h"
#include "versioncreator.h"

class VersionManager {
private:
    fs::path versions_path;
    std::stack<Version> history;
    ILogger* logger;
    IVersionCreator* version_creator;
public:
    VersionManager(): logger(new Logger()), version_creator(new VersionCreator()) {};
    VersionManager(ILogger* _logger, IVersionCreator* _version_creator) {
        logger = _logger;
        version_creator = _version_creator;
    };

    void set_versions_path(const fs::path& source);
    fs::path get_versions_path();
    void CreateVersion();
    void DeleteVersion(const Version&);
    std::stack<Version> GetVersionHistoryForFile(const std::string& filename);
};


#endif //FILE_SYNCHRONIZER_VERSIONMANAGER_H
