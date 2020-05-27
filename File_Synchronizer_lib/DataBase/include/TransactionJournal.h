#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <utility>
#include <vector>

#include "Transaction.h"

class ITransactionJournal {
public:
    virtual void AddTransaction(Transaction) = 0;
    virtual void FixTransaction(){};
};

class TransactionJournal : public ITransactionJournal {
private:
    std::filesystem::path journalPath;
    std::vector<Transaction> transactionList;
public:
    TransactionJournal(const std::filesystem::path& source) {
        journalPath = source / "journal.json";
    };
    ~TransactionJournal() = default;

    void AddTransaction(Transaction transaction) override;
    // Записать текущий журнал транзакций в файл journalPath и очистить
    void FixTransaction() override;
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
