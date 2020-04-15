//
// Created by Administrator on 10.04.2020.
//

#ifndef UNTITLED9_VERSIONMANAGER_H
#define UNTITLED9_VERSIONMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <filesystem>


class VersionHistoryManager {
private:
    std::filesystem::path version_path;
    std::map<std::string, std::stack<std::string>> files_versions;
public:
    std::filesystem::path get_version_path();
    void set_version_path(const std::filesystem::path& source);

    auto GetFullVersionHistory();
    auto GetVersionHistoryByFilename(const std::string& filename);

    int AddVersionToFileHistory(const std::string& filename, const std::string& versionfile);
    std::filesystem::path GetLastFileVersionFromFileHistory(const std::string& filename);
    void DeleteLastVersionFromFileHistory(const std::string& filename);

    int GetCountSyncFiles();

    std::vector<std::string> GetSyncFilesList();

    std::filesystem::path CreateDiffForFile(const std::string& filename);

};

#endif //UNTITLED9_VERSIONMANAGER_H
