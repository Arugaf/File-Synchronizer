#ifndef FILE_SYNCHRONIZER_CLASS_H
#define FILE_SYNCHRONIZER_CLASS_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include <boost/asio.hpp>


class dispatcher_server_connections {
    public:
        dispatcher_server_connections(std::string recieved_port) {
            port = recieved_port;
        }
        int new_connection(int, int, std::string);
        int disconnect(int, int);
        std::vector<std::string> return_connections(int);
    private:
        std::vector<std::string> ping_connections(std::vector<std::string>&);
        std::string port;
};

class dispatcher_server_users {
    public:
        int auth_try(std::string, std::string);
        int add_user(std::string, std::string);
        int edit_user(int, std::string, std::string);
};

class dispatcher_database_wrapper {
    public:
        dispatcher_database_wrapper(std::string path) {
            database = sqlite3_open(path.c_str(), &db);
            err = 0;
        }
        ~dispatcher_database_wrapper() {
            sqlite3_close(db);
            sqlite3_free(err);
        }
        int db_insert(std::string, std::vector<std::string>&, std::vector<std::string>&);
        int db_delete(std::string, std::vector<std::string>&, std::vector<std::string>&);
        int db_update(std::string, std::string, std::string, std::vector<std::string>&, std::vector<std::string>&);
        std::vector<std::string> db_select(std::string, std::string, std::vector<std::string>&, std::vector<std::string>&);
        std::vector<std::string> db_select(std::string, std::string);
    private:
        sqlite3 *db;
        int database;
        std::string base_path;
        char *err;
};

class dispatcher_pc_id_dispenser {
    public:
        dispatcher_pc_id_dispenser() {
            dispatcher_database_wrapper wrapper("Database.db");
            std::vector<std::string> result = wrapper.db_select("connections","connection_pc_id");
            if (result.front().compare("NONE") == 0) {
                last_pc_id = 0;
            } else {
                last_pc_id = std::stoi(result.back());
            }
        }
        int return_new_pc_id();
    private:
        int last_pc_id;
};


#endif //FILE_SYNCHRONIZER_CLASS_H
