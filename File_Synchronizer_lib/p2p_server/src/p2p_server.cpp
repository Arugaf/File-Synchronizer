#include "p2p_server.h"
class socket;

p2p_server::p2p_server() {

};

p2p_server::~p2p_server() {

};

vector <std::string> p2p_server::return_ip_list() {
    vector <std::string> list = {"NULL"};

    return list;
}

vector <socket> p2p_server::init_all_connections() {
    vector <socket> list;

    return list;
}

int p2p_server::ping_open_connections() {
    return 1;
}

int p2p_server::return_connection_closed() {
    return 1;
}
