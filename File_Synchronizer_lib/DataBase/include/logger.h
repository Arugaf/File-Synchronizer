#ifndef FILE_SYNCHRONIZER_LOGGER_H
#define FILE_SYNCHRONIZER_LOGGER_H

#include <filesystem>
namespace fs = std::filesystem;

#include "transaction.h"
#include "transactionjournal.h"

class ILogger {
public:
    virtual void CreateTransaction(const std::string&);
};

class Logger : public ILogger {
private:
    ITransactionJournal* journal;
public:
    Logger(): journal(new TransactionJournal()) {};
    Logger(ITransactionJournal* _journal) {
        journal = _journal;
    };

    void CreateTransaction(const std::string& message) override;
};

#endif //FILE_SYNCHRONIZER_LOGGER_H
