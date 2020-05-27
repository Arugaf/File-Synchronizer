#ifndef FILE_SYNCHRONIZER_TRANSACTION_H
#define FILE_SYNCHRONIZER_TRANSACTION_H

#include <filesystem>
#include <utility>
#include <ctime>

enum class Operation {
    created,
    deleted,
    modified
};

struct Transaction {
    std::filesystem::path target;
    std::chrono::system_clock::time_point lastOperationTime;
    Operation operation;

    Transaction(const Operation& _operation, std::filesystem::path _target):
                operation(_operation), lastOperationTime(std::chrono::system_clock::now()), target(std::move(_target)) {};
};



#endif //FILE_SYNCHRONIZER_TRANSACTION_H
