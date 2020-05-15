#ifndef FILE_SYNCHRONIZER_USER_H
#define FILE_SYNCHRONIZER_USER_H

#include <string>
#include <utility>
#include <unordered_set>

#include "machine.h"

class User {
private:
    std::string username;
    std::unordered_set<int> connectedMachines;
public:
    User(): username("undefined") {};
    User(std::string _username): username(std::move(_username)) {};
    virtual ~User() = default;

    void SetUsername(const std::string& name);
    std::string GetUsername();
    std::unordered_set<int> GetConnectedMachines();
    int GetCountConnectedMachines();
    void AddConnectedMachine(Machine machine);
    void AddConnectedMachine(const int& machine);
    void DeleteConnectedMachine(Machine machine);
    void DeleteConnectedMachine(const int& machine);

    void Print(std::ostream &out);
};


#endif //FILE_SYNCHRONIZER_USER_H
