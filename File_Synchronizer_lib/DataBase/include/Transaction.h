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

std::string_view ConvertToString(Operation operation) {
    switch (operation) {
        case Operation::created: return "created";
        case Operation::deleted: return "deleted";
        case Operation::modified: return "modified";
    }
}

struct Transaction {
    std::filesystem::path target;
    std::chrono::system_clock::time_point lastOperationTime;
    Operation operation;

    Transaction(const Operation& _operation, std::filesystem::path _target):
                operation(_operation), lastOperationTime(std::chrono::system_clock::now()), target(std::move(_target)) {};
};



#endif //FILE_SYNCHRONIZER_TRANSACTION_H
