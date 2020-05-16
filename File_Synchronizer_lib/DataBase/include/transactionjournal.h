#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <vector>

#include "transaction.h"

class ITransactionJournal {
public:
    virtual void AddTransaction(Transaction) = 0;
    virtual void DeleteLastTransaction(){};
    virtual void Clear(){};
    virtual int GetJournalSize(){};
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
    void DeleteLastTransaction() override;
    void Clear() override;
    int GetJournalSize() override;
    void FixJournal() override;
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
