#include "user.h"

void User::SetUsername(const std::string &name) {
    username = name;
}

std::string User::GetUsername() {
    return username;
}

std::unordered_set<int> User::GetConnectedMachines() {
    return connectedMachines;
}

int User::GetCountConnectedMachines() {
    return connectedMachines.size();
}

void User::AddConnectedMachine(Machine machine) {
    connectedMachines.insert(machine.GetId());
}

void User::AddConnectedMachine(const int &machine) {
    connectedMachines.insert(machine);
}

void User::DeleteConnectedMachine(Machine machine) {
    connectedMachines.erase(machine.GetId());
}

void User::DeleteConnectedMachine(const int &machine) {
    connectedMachines.erase(machine);
}


void User::Print(std::ostream &out) {
    std::string info;

    info = username + "\n";

    for (auto item : connectedMachines) {
        info += std::to_string(item);
        info += " ";
    }

    out << info;
}

