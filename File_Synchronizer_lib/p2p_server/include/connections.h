#ifndef PROJECT_CONNECTIONS_H
#define PROJECT_CONNECTIONS_H

#include <string>

class connection{
public:

    connection();

    ~connection();

    int init_connection();

    int close_connection();

    int get_socket();

    int ping_connection();

    int return_connection_close();

private:

    std::string ip;

};


#endif //PROJECT_CONNECTIONS_H
