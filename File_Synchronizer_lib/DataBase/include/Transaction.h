#ifndef FILE_SYNCHRONIZER_TRANSACTION_H
#define FILE_SYNCHRONIZER_TRANSACTION_H

#include <filesystem>
#include <tuple>
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


    typedef std::filesystem::path path;
    typedef std::chrono::system_clock::time_point timePoint;
    [[nodiscard]] virtual std::tuple<path, timePoint, Operation> GetRecord() const {
        {
            return std::make_tuple(target, lastOperationTime, operation);
        }
    }

};


#endif //FILE_SYNCHRONIZER_TRANSACTION_H
