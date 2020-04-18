#ifndef FILE_SYNCHRONIZER_FILE_H
#define FILE_SYNCHRONIZER_FILE_H

#include <filesystem>
#include <string>
namespace fs = std::filesystem;

class File {
private:
    std::string filename;
    fs::path file_path;
    bool blacklist;
public:
    void set_filename(const std::string& name);
    std::string get_filename();
    void set_file_path(const fs::path& source);
    fs::path get_file_path();
    bool IsInBlacklist();
    void AddFileToBlacklist();
    void DeleteFileFromBlacklist();
};

#endif //FILE_SYNCHRONIZER_FILE_H
