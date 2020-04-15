#include "gtest/gtest.h"
#include "sqlite3/sqlite3.h"

#include "class.h"

TEST(DispatcherServer, NewConnectionTest) {
    new_connection(-1, -1, "test");
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_ip FROM FS_ACTIVE_USERS WHERE user_id = '-1';";
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_STREQ(sqlite3_exec(db, SQL, 0, 0, &err), "test");
    sqlite3_close(db);
    disconnect(-1, -1);
}

TEST(DispatcherServer, DisconnectTest) {
    new_connection(-1, -1, "test");
    disconnect(-1, -1);
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_ip FROM FS_ACTIVE_USERS WHERE user_id = '-1';";
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_STREQ(sqlite3_exec(db, SQL, 0, 0, &err), "SQLITE_DONE");
    sqlite3_close(db);
}

TEST(DispatcherServer, ReturnConnectionsTest) {
    new_connection(-1, -1, "test");
    ASSERT_STREQ(return_connections(-1).back, "test");
    disconnect(-1, -1);
}

TEST(DispatcherServer, NewPcIdTest) {
    int new_pc_id = return_new_pc_id();
    ASSERT_EQ(new_pc_id, last_pc_id);
}

TEST(DispatcherServer, CreateUserTest) {
    add_user("test", "test");
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_id FROM FS_USERS WHERE login='test' AND password='test';"
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_STRNE(sqlite3_exec(db, SQL, 0, 0, &err), "SQLITE_DONE");
    sqlite3_close(db);
}

TEST(DispatcherServer, AuthTest) {
    int user_id = auth_try("test", "test");
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_id FROM FS_USERS WHERE login='test' AND password='test';"
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_EQ(atoi(sqlite3_exec(db, SQL, 0, 0, &err)), user_id);
    sqlite3_close(db);
}

TEST(DispatcherClient, EditUserTest) {
    edit_user(-1, "test2", "test2");
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_id FROM FS_USERS WHERE login='test2' AND password='test2';"
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_EQ(atoi(sqlite3_exec(db, SQL, 0, 0, &err)), -1);
    char* deleting = "DELETE FROM FS_USERS where user_id = '-1'";
    sqlite3_exec(db, deleting, 0, 0, &err);
    sqlite3_close(db);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
