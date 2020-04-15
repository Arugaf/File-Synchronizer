#include "gtest/gtest.h"
#include "sqlite3/sqlite3.h"

#include "class.h"

TEST(DispatcherClient, CreateUserTest) {
    user_create("test", "test");
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_id FROM FS_USERS WHERE login='test' AND password='test';"
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_STRNE(sqlite3_exec(db, SQL, 0, 0, &err), "SQLITE_DONE");
    sqlite3_close(db);
}

TEST(DispatcherClient, LoginTest) {
    int user_id = user_login("test", "test");
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_id FROM FS_USERS WHERE login='test' AND password='test';"
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_EQ(atoi(sqlite3_exec(db, SQL, 0, 0, &err)), user_id);
    sqlite3_close(db);
    user_logout();
}


TEST(DispatcherClient, EditUserTest) {
    int user_id = user_login("test", "test");
    user_edit("test2", "test2");
    ASSERT_EQ(user_id, user_login("test2", "test2"));
    user_logout();
}

TEST(DispatcherClient, LogoutTest) {
    user_login("test", "test");
    user_logout();
    sqlite3 *db = 0;
    char *err = 0;
    char* SQL = "SELECT user_id FROM FS_ACTIVE_USERS WHERE pc_id = '";
    strcat(SQL, itoa(pc_id));
    strcat(SQL, "';");
    ASSERT_STREQ(sqlite3_open("database.dblite", &db), "SQLITE_OK");
    ASSERT_STREQ(sqlite3_exec(db, SQL, 0, 0, &err), "SQLITE_DONE");
    sqlite3_close(db);
}

TEST(DispatcherClient, LogoutTest) {
    int user_id = user_login("test", "test");
    ASSERT_NE(return_connections(user_id).size, 0);
    user_logout();
}

TEST(DispatcherClient, IpEstablishTest) {
    ASSERT_NE(establish_ip(), 0);
}

TEST(DispatcherClient, RecievindTest) {
    ASSERT_NE(recieve_pc_id(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
