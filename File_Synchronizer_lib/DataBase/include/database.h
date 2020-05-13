#ifndef FILE_SYNCHRONIZER_DATABASE_H
#define FILE_SYNCHRONIZER_DATABASE_H

#include <filesystem>

class Database {
private:
    std::filesystem::path dbPath;
public:
    virtual ~Database() = default;

    void SetDbPath(const std::filesystem::path& source);
    std::filesystem::path GetDbPath();
    std::filesystem::path GetFileInfofile(const std::string& filename);
    std::filesystem::path GetFileInfofile();
    std::filesystem::path GetUserInfofile(const std::string& username);
    std::filesystem::path GetUserInfofile();
    std::filesystem::path GetJournal();
    std::filesystem::path GetVersions();
    std::filesystem::path GetAllVersionsForFile(const std::string& filename);
    std::filesystem::path GetLastVersionForFile(const std::string& filename);
    std::filesystem::path GetMachineInfofile();
    std::filesystem::path GetDB();
};


#endif //FILE_SYNCHRONIZER_DATABASE_H
