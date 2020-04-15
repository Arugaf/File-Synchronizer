//
// Created by Administrator on 14.04.2020.
//

#ifndef UNTITLED9_USERMANAGER_H
#define UNTITLED9_USERMANAGER_H

#include "user.h"

#include <filesystem>


class UserManager {
private:
    std::filesystem::path userinfo_path;
public:
    std::filesystem::path get_userinfo_path();
    void set_userinfo_path(const std::filesystem::path& source);

    int CreateUserInfo(const User& user);
    void UpdateUserInfo(const User& user);
    int DeleteUserInfo(const std::string& user);

    std::filesystem::path GetUsersInfo();
    std::filesystem::path GetUserInfoByUsername(const std::string& user);
};

#endif //UNTITLED9_USERMANAGER_H
