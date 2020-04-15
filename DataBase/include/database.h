//
// Created by Administrator on 15.04.2020.
//

#ifndef UNTITLED9_DATABASE_H
#define UNTITLED9_DATABASE_H

#include "user.h"
#include "machine.h"

class DataBase {
public:
    User& get_user() {
        return user;
    }
    Machine& get_machine() {
        return machine;
    }
private:
    //TODO: PIMPL
    User user;
    Machine machine;
};

#endif //UNTITLED9_DATABASE_H
