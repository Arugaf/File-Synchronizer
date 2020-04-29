#include "class.h"

int dispatcher_server_connections::new_connection(int user_id, int pc_id, std::string recieved_ip) {
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"connection_user_id", "connection_pc_id", "connection_ip"};
    std::vector<std::string> arguments = {std::to_string(user_id), std::to_string(pc_id), recieved_ip};
    int result = wrapper.db_insert("connections", columns, arguments);
    return result;
}

int dispatcher_server_connections::disconnect(int user_id, int pc_id) {
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"connection_user_id", "connection_pc_id"};
    std::vector<std::string> arguments = {std::to_string(user_id), std::to_string(pc_id)};
    int result = wrapper.db_delete("connections", columns, arguments);
    return result;
}

std::vector<std::string> dispatcher_server_connections::return_connections(int user_id) {
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"connection_user_id"};
    std::vector<std::string> arguments = {std::to_string(user_id)};
    std::vector<std::string> result = wrapper.db_select("connections", "connection_ip", columns, arguments);
    if (result.front().compare("NONE") != 0) {
        return ping_connections(result);
    } else {
        return {};
    }
}

std::vector<std::string> dispatcher_server_connections::ping_connections(std::vector<std::string>& ip_list) {
    std::vector<std::string> still_active;
    for (auto ip = ip_list.begin(); ip != ip_list.end(); ip++) {
        try {
        boost::asio::io_service ios;
        boost::asio::ip::tcp::resolver::query resolver_query(*ip, port, boost::asio::ip::tcp::resolver::query::numeric_service);
        boost::asio::ip::tcp::resolver resolver(ios);
        boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(resolver_query);
        boost::asio::ip::tcp::socket sock(ios);
        boost::asio::connect(sock, it);
        } catch (boost::system::system_error &e) {
            //std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;
            continue;
        }
        still_active.push_back(*ip);
    }
    return still_active;
}

int dispatcher_server_users::auth_try(std::string login, std::string password) {
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"user_login", "user_password"};
    std::vector<std::string> arguments = {login, password};
    std::vector<std::string> result = wrapper.db_select("users", "user_id", columns, arguments);
    if (result.front().compare("NONE") != 0) {
        return std::stoi(result.front());
    } else {
        return -1;
    }
}

int dispatcher_server_users::add_user(std::string login, std::string password) {
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"user_login"};
    std::vector<std::string> arguments = {login};
    std::vector<std::string> result = wrapper.db_select("users", "user_id", columns, arguments);
    if (result.front().compare("NONE") != 0) {
        return -1;
    } else {
        columns.push_back("user_password");
        arguments.push_back(password);
        int result = wrapper.db_insert("users",columns,arguments);
        if (result == -1) {
            return -2;
        } else {
            std::vector<std::string> fetch = wrapper.db_select("users", "user_id", columns, arguments);
            return std::stoi(fetch.front());
        }
    }
}

int dispatcher_server_users::edit_user(int user_id, std::string new_login, std::string new_password) {
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"user_id"};
    std::vector<std::string> arguments = {std::to_string(user_id)};
    std::vector<std::string> result = wrapper.db_select("users", "user_id", columns, arguments);
    if (result.front().compare("NONE") == 0) {
        return -1;
    } else {
        int result = wrapper.db_update("users", "user_login", new_login, columns, arguments);
        if (result == -1) {
            return -2;
        }
        result = wrapper.db_update("users", "user_password", new_password, columns, arguments);
        if (result == -1) {
            return -3;
        }
        return 0;
    }
}

int dispatcher_database_wrapper::db_insert(std::string table, std::vector<std::string>& columns, std::vector<std::string>& arguments) {
    auto vector_content = columns.begin();
    std::string sql = "INSERT INTO " + table + " (" + *vector_content;
    for (vector_content++; vector_content != columns.end(); vector_content++) {
        sql = sql + ", " + *vector_content;
    }
    vector_content = arguments.begin();
    sql = sql + ") VALUES (\"" + *vector_content;
    for (vector_content++; vector_content != arguments.end(); vector_content++) {
        sql = sql + "\", \"" + *vector_content;
    }
    sql = sql + "\");";

    database = sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
    if(database != SQLITE_OK) {
        return -1;
    } else {
        return 0;
    }
}

int dispatcher_database_wrapper::db_delete(std::string table, std::vector<std::string>& columns, std::vector<std::string>& arguments) {
    auto columns_content = columns.begin();
    auto arguments_content = arguments.begin();
    std::string sql = "DELETE FROM " + table + " WHERE (" + *columns_content + " = \"" + *arguments_content;
    for (columns_content++, arguments_content++; columns_content != columns.end(); columns_content++, arguments_content++) {
        sql = sql + "\" AND " + *columns_content + " = \"" + *arguments_content;
    }
    sql = sql + "\");";

    database = sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
    if(database != SQLITE_OK) {
        return -2;
    } else {
        return 0;
    }
}

int dispatcher_database_wrapper::db_update(std::string table, std::string upatable_column, std::string updatable_value, std::vector<std::string>& columns, std::vector<std::string>& arguments) {
    auto columns_content = columns.begin();
    auto arguments_content = arguments.begin();
    std::string sql = "UPDATE " + table + " SET " + upatable_column + " = \"" + updatable_value + "\" WHERE (" + *columns_content + " = \"" + *arguments_content;
    for (columns_content++, arguments_content++; columns_content != columns.end(); columns_content++, arguments_content++) {
        sql = sql + "\" AND " + *columns_content + " = \"" + *arguments_content;
    }
    sql = sql + "\");";
    
    database = sqlite3_exec(db, sql.c_str(), NULL, 0, &err);
    if(database != SQLITE_OK) {
        return -1;
    } else {
        return 0;
    }
}

std::vector<std::string> dispatcher_database_wrapper::db_select(std::string table, std::string select, std::vector<std::string>& columns, std::vector<std::string>& arguments) {
    sqlite3_stmt* stmt;
    auto columns_content = columns.begin();
    auto arguments_content = arguments.begin();
    std::string sql = "SELECT " + select + " FROM " + table + " WHERE (" + *columns_content + " = \"" + *arguments_content;
    for (columns_content++, arguments_content++; columns_content != columns.end(); columns_content++, arguments_content++) {
        sql = sql + "\" AND " + *columns_content + " = \"" + *arguments_content;
    }
    sql = sql + "\");";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        return {};
    }
    std::vector<std::string> result;
    while((sqlite3_step(stmt)) == SQLITE_ROW) {
        result.push_back((char*)sqlite3_column_text(stmt, 0));
    }
    if (result.size() == 0) {
        result.push_back("NONE");
    }
    return result;
}

std::vector<std::string> dispatcher_database_wrapper::db_select(std::string table, std::string select) {
    sqlite3_stmt* stmt;
    std::string sql = "SELECT " + select + " FROM " + table + ";";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        return {};
    }
    std::vector<std::string> result;
    while((sqlite3_step(stmt)) == SQLITE_ROW) {
        result.push_back((char*)sqlite3_column_text(stmt, 0));
    }
    if (result.size() == 0) {
        result.push_back("NONE");
    }
    return result;
}

int dispatcher_pc_id_dispenser::return_new_pc_id() {
    return ++last_pc_id;
}
