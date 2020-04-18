#ifndef FILE_SYNCHRONIZER_USER_INFO_FILEMANAGER_H
#define FILE_SYNCHRONIZER_USER_INFO_FILEMANAGER_H

#include <filesystem>
namespace fs = std::filesystem;

#include "i_filemanager.h"
#include "user.h"
#include "logger.h"

class UserInfoFileManager : public IFileManager<User> {
private:
    fs::path users_path;
    ILogger* logger;
public:
    UserInfoFileManager(): logger(new Logger()) {};
    UserInfoFileManager(ILogger* _logger) {
        logger = _logger;
    };

    void set_users_path(const fs::path& source);
    fs::path get_users_path();
    void Create(const User& user) override;
    void Delete(const User& user) override;
    void Update(const User& user) override;
    User GetUserByUsername(const std::string& username);
};


#endif //FILE_SYNCHRONIZER_USER_INFO_FILEMANAGER_H
