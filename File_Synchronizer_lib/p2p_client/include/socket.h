#ifndef PROJECT_SOCKET_H
#define PROJECT_SOCKET_H

class socket;

class socket_controller {

public:

    socket_controller();

    socket_controller(std::string ip);

    ~socket_controller();

    int make_socket(std::string);

    socket return_socket();

    int set_socket_ip(std::string);

private:

    socket curr_socket;

    std::string ip;
};

#endif //PROJECT_SOCKET_H
