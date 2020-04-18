#ifndef FILE_SYNCHRONIZER_TRANSACTION_H
#define FILE_SYNCHRONIZER_TRANSACTION_H

#include <filesystem>
namespace fs = std::filesystem;

enum Operation {
    created,
    deleted,
    added,
    edited
};

class ITransaction {
public:
    virtual ~ITransaction() = 0;
};

class Transaction : public ITransaction {
private:
    Operation operation;
    fs::path target;
    int source_machine;
public:
};

#endif //FILE_SYNCHRONIZER_TRANSACTION_H
