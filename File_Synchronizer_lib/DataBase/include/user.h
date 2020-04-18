#ifndef FILE_SYNCHRONIZER_USER_H
#define FILE_SYNCHRONIZER_USER_H

#include <string>
#include <vector>

#include "machine.h"

class User {
private:
    std::string username;
    std::vector<Machine> connected_machines;
public:
    void set_username(const std::string& name);
    std::string get_username();
    std::vector<Machine> get_connected_machines();
    int GetCountConnectedMachines();
    void AddConnectedMachine(const Machine&);
    void DeleteConnectedMachine(const Machine&);
};


#endif //FILE_SYNCHRONIZER_USER_H
