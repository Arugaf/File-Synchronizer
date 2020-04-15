#ifndef PROJECT_P2P_SERVER_H
#define PROJECT_P2P_SERVER_H

#include <connections.h>
#include <ip_list.h>

class socket;

class p2p_server{

public:

    p2p_server();

    ~p2p_server();

    vector <std::string> return_ip_list();

    vector <socket> init_all_connections();

    int ping_open_connections();

    int return_connection_closed();

private:

   vector <socket> *socket_list;

};

#endif //PROJECT_P2P_SERVER_H
