//
// Created by Administrator on 15.04.2020.
//

#ifndef FILE_SYNCHRONIZER_DATABASE_H
#define FILE_SYNCHRONIZER_DATABASE_H

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

#endif //FILE_SYNCHRONIZER_DATABASE_H
