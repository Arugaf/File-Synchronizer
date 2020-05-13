#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <vector>

#include "transaction.h"

class ITransactionJournal {
public:
    virtual void AddTransaction(Transaction) = 0;
    virtual void DeleteTransaction() = 0;
    virtual void Clear() = 0;
    virtual int GetJournalSize() = 0;
    virtual void FixJournal(){};
};

// TODO: boost XML для транзакций
class TransactionJournal : public ITransactionJournal {
private:
    std::filesystem::path journalPath;
    std::vector<Transaction> transactionList;
    int currentTransaction;
public:
    TransactionJournal(): currentTransaction(0) {};
    ~TransactionJournal() = default;


    void SetJournalPath(const std::filesystem::path &source);
    std::filesystem::path GetJournalPath();
    std::vector<Transaction> GetTransactionList();
    void AddTransaction(Transaction transaction) override;
    void DeleteTransaction() override;
    void Clear() override;
    int GetJournalSize() override;
    void FixJournal() override;
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
