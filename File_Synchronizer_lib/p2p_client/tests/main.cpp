#include "gtest/gtest.h"

#include "socket.h"
#include "p2p_client.h"

TEST(socket, make_socket_test) {

    ASSERT_NE(make_socket("192.168.0.0"), 0);
}

TEST(socket, return_socket_test) {
    ASSERT_NE(return_socket(), 0);
}

TEST(socket, set_socket_ip_test) {
    std::string ip_set = "192.168.0.0";
    set_socket_ip(ip);
    ASSERT_STREQ(ip, ip_set);
}

TEST(p2p_client, wait_for_connection_test) {
    ASSERT_NE(wait_for_connection(), 0);
}

TEST(p2p_client, process_income_connection_test) {
    ASSERT_NE(process_income_connection(), 0);
}

TEST(p2p_client, ping_connection_test) {
    ASSERT_NE(ping_connection(), 0);
}

TEST(p2p_client, close_connection_test) {
    ASSERT_NE(close_connection(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
