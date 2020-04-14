#ifndef FILE_SYNCHRONIZER_CLASS_H
#define FILE_SYNCHRONIZER_CLASS_H

#include <string>

class dispatcher_client {
    public:
        int user_login(std::string, std::string);
        int user_create(std::string, std::string);
        int user_edit(std::string, std::string);
        int user_logout();
    private:
        std::string establish_ip();
        std::string crypt(std::string);
        int disconnect();
        int recieve_pc_id();
        int current_user_id;
        int pc_id;
        std::string current_ip;
};

#endif //FILE_SYNCHRONIZER_CLASS_H
