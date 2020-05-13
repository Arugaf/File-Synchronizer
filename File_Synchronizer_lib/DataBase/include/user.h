#ifndef FILE_SYNCHRONIZER_USER_H
#define FILE_SYNCHRONIZER_USER_H

#include <string>
#include <utility>
#include <vector>

#include "machine.h"

class User {
private:
    std::string username;
    std::vector<int> connectedMachines;
public:
    User(): username("undefined") {};
    User(std::string _username): username(std::move(_username)) {};
    virtual ~User() = default;

    void SetUsername(const std::string& name);
    std::string GetUsername();
    std::vector<int> GetConnectedMachines();
    int GetCountConnectedMachines();
    void AddConnectedMachine(Machine machine);
    void AddConnectedMachine(const int& machine);
    void DeleteConnectedMachine(Machine machine);
    void DeleteConnectedMachine(const int& machine);

    void Print(std::ostream &out);
};


#endif //FILE_SYNCHRONIZER_USER_H
