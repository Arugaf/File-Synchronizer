#ifndef PROJECT_SOCKET_H
#define PROJECT_SOCKET_H

class socket;

class socket_controller {

public:

    socket_controller();

    socket_controller(std::string ip);

    ~socket_controller();

    int make_socket();

    int return_socket();

private:

    socket curr_socket;
};

#endif //PROJECT_SOCKET_H
