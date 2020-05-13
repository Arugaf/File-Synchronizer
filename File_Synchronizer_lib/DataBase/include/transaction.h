#ifndef FILE_SYNCHRONIZER_TRANSACTION_H
#define FILE_SYNCHRONIZER_TRANSACTION_H

#include <filesystem>
#include <utility>

enum Operation {
    created,
    deleted,
    edited,
    NotDefined
};

class ITransaction {
private:
    std::string message;
public:
    void SetMessage(const std::string& _message) {
        message = _message;
    }
    virtual std::string GetMessage() {
        return message;
    }

    bool operator==(const ITransaction& right) {
        return this->message == right.message;
    }
};


class Transaction : public ITransaction {
private:
    Operation operation;
    std::filesystem::path target;
    int sourceMachine;
public:
    Transaction(): operation(NotDefined), sourceMachine(-1) {};
    Transaction(const Operation& _operation, std::filesystem::path _target, const int& _id):
                operation(_operation), target(std::move(_target)), sourceMachine(_id) {};
    void FormMessage();
    std::tuple<Operation, std::filesystem::path, int> GetParams();

    void Print(std::ostream &out);
};

#endif //FILE_SYNCHRONIZER_TRANSACTION_H
