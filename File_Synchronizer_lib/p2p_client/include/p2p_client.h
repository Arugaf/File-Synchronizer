#ifndef PROJECT_P2P_CLIENT_H
#define PROJECT_P2P_CLIENT_H

#include "socket.h"

class p2p_client {

public:

    p2p_client();

    ~p2p_client();

    int wait_for_connection();

    int process_income_connection();

    int ping_connection();

    int close_connection();

private:

    std::string ip;

};

#endif //PROJECT_P2P_CLIENT_H
