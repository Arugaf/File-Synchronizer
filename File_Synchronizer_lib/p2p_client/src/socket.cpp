#include "socket.h"

socket_controller::socket_controller() {

}

socket_controller::socket_controller(std::string ip) {

}

socket_controller::~socket_controller() {

}

int socket_controller::make_socket(std::string) {
    return 1;
}

socket socket_controller::return_socket() {
    socket a;
    return a;
}

int set_socket_ip(std::string) {
    return 1;
}


