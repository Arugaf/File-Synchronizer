#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <vector>
namespace fs = std::filesystem;

#include "transaction.h"

class ITransactionJournal {
public:
    virtual void AddTransaction(const Transaction&) = 0;
    virtual void DeleteTransaction(const Transaction&) = 0;
    virtual void Clear() = 0;
};

class TransactionJournal : public ITransactionJournal {
private:
    fs::path journal_path;
    std::vector<Transaction> transaction_list;
    int current_transaction;
public:
    TransactionJournal(): current_transaction(0) {};
    ~TransactionJournal() = default;

    void set_journal_path(const fs::path& source);
    fs::path get_journal_path();
    std::vector<Transaction> get_transaction_list();
    void AddTransaction(const Transaction& transaction) override;
    void DeleteTransaction(const Transaction& transaction) override;
    void Clear() override;
    void FixJournal();
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
