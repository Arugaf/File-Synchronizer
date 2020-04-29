#include <gtest/gtest.h>

#include "class.h"

TEST(DispatcherServer, AddUserTest) {
    dispatcher_server_users user;
    int id = user.add_user("1","1");
    ASSERT_GT(id, 0);
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"user_login", "user_password"};
    std::vector<std::string> args = {"1", "1"};
    std::vector<std::string> result = wrapper.db_select("users", "user_id", columns, args);
    ASSERT_EQ(std::stoi(result.front()), id);
    wrapper.db_delete("users", columns, args);
}

TEST(DispatcherServer, AuthTryTest) {
    dispatcher_server_users user;
    user.add_user("1","1");
    int id = user.auth_try("1","1");
    ASSERT_GT(id, 0);
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"user_login", "user_password"};
    std::vector<std::string> args = {"1", "1"};
    std::vector<std::string> result = wrapper.db_select("users", "user_id", columns, args);
    ASSERT_EQ(std::stoi(result.front()), id);
    wrapper.db_delete("users", columns, args);
}

TEST(DispatcherServer, EditUserTest) {
    dispatcher_server_users user;
    int id = user.add_user("1","1");
    user.edit_user(id, "2", "2");
    int new_id = user.auth_try("2","2");
    ASSERT_EQ(id, new_id);
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"user_login", "user_password"};
    std::vector<std::string> args = {"2", "2"};
    wrapper.db_delete("users", columns, args);
}

TEST(DispatcherServer, NewConnectionTest) {
    dispatcher_server_connections connections("80");
    int result = connections.new_connection(0, 1, "localhost");
    result += connections.new_connection(0, 2, "localhost");
    result += connections.new_connection(0, 3, "localhost");
    ASSERT_EQ(result, 0);
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"connection_user_id"};
    std::vector<std::string> args = {"0"};
    std::vector<std::string> fetch = wrapper.db_select("connections", "connection_id", columns, args);
    ASSERT_EQ(fetch.size(), 3);
    wrapper.db_delete("connections", columns, args);
}

TEST(DispatcherServer, DisconnectTest) {
    dispatcher_server_connections connections("80");
    connections.new_connection(0, 1, "localhost");
    connections.new_connection(0, 2, "localhost");
    connections.new_connection(0, 3, "localhost");
    connections.disconnect(0, 3);
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> columns = {"connection_user_id"};
    std::vector<std::string> args = {"0"};
    std::vector<std::string> fetch = wrapper.db_select("connections", "connection_id", columns, args);
    ASSERT_EQ(fetch.size(), 2);
    wrapper.db_delete("connections", columns, args);
}

TEST(DispatcherServer, PcIdDispenserTest) {
    dispatcher_pc_id_dispenser dispenser;
    dispatcher_database_wrapper wrapper("Database.db");
    std::vector<std::string> fetch = wrapper.db_select("connections", "connection_pc_id");
    ASSERT_EQ(std::stoi(fetch.back()), dispenser.return_new_pc_id() - 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
