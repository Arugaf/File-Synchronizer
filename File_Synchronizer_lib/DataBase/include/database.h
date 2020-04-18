#ifndef FILE_SYNCHRONIZER_DATABASE_H
#define FILE_SYNCHRONIZER_DATABASE_H

#include <filesystem>
namespace fs = std::filesystem;

class Database {
private:
    fs::path db_path;
public:
    void set_db_path(const fs::path& source);
    fs::path get_db_path();
    fs::path GetFileInfofile(const std::string& filename);
    fs::path GetFileInfofile();
    fs::path GetUserInfofile(const std::string& username);
    fs::path GetUserInfofile();
    fs::path GetJournal();
    fs::path GetVersions();
    fs::path GetAllVersionsForFile(const std::string& filename);
    fs::path GetLastVersionForFile(const std::string& filename);
    fs::path GetMachineInfofile();
    fs::path GetDB();
};


#endif //FILE_SYNCHRONIZER_DATABASE_H
