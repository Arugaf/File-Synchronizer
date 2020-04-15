#ifndef FILE_SYNCHRONIZER_CLASS_H
#define FILE_SYNCHRONIZER_CLASS_H

#include <string>
#include <vector>

class dispatcher_server_connections {
    public:
        int new_connection(int, int, std::string);
        int disconnect(int, int);
        std::vector<std::string> return_connections(int);
        int return_new_pc_id();
    private:
        std::vector<std::string> ping_connection(std::vector<std::string>);
        int last_pc_id;
};

class dispatcher_server_users {
    public:
        int auth_try(std::string, std::string);
        int add_user(std::string, std::string);
        int edit_user(int, std::string, std::string);
};


#endif //FILE_SYNCHRONIZER_CLASS_H
