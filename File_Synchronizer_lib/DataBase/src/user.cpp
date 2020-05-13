#include "user.h"

void User::SetUsername(const std::string &name) {
    username = name;
}

std::string User::GetUsername() {
    return username;
}

std::vector<int> User::GetConnectedMachines() {
    return connectedMachines;
}

int User::GetCountConnectedMachines() {
    return connectedMachines.size();
}

void User::AddConnectedMachine(Machine machine) {
    connectedMachines.push_back(machine.GetId());
}

void User::AddConnectedMachine(const int &machine) {
    connectedMachines.push_back(machine);
}

void User::DeleteConnectedMachine(Machine machine) {
    connectedMachines.erase(std::remove(connectedMachines.begin(),
                            connectedMachines.end(), machine.GetId()), connectedMachines.end());
}

void User::DeleteConnectedMachine(const int &machine) {
    connectedMachines.erase(std::remove(connectedMachines.begin(),
                                        connectedMachines.end(), machine), connectedMachines.end());
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

