#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <utility>
#include <vector>

#include "transaction.h"

class ITransactionJournal {
public:
    virtual void AddTransaction(Transaction) = 0;
    virtual void Clear(){};
    virtual int GetJournalSize(){};
    virtual void FixJournal(){};
};

class TransactionJournal : public ITransactionJournal {
private:
    std::filesystem::path journalPath;
    std::vector<Transaction> transactionList;
public:
    TransactionJournal() = default;
    TransactionJournal(const std::filesystem::path& source) {
        journalPath = source / "journal.json";
    };
    ~TransactionJournal() = default;

    void AddTransaction(Transaction transaction) override;
    void Clear() override;
    int GetJournalSize() override;

    // Записать текущий журнал транзакций в файл journalPath
    void FixJournal() override;
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
