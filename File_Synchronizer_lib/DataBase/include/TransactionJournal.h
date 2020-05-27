#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <utility>
#include <vector>

#include "Transaction.h"

template <typename TransactionRecord>
class ITransactionJournal {
public:
    virtual void AddTransaction(TransactionRecord) = 0;
    TransactionRecord GetLastTransaction() {};
    void DeleteLastTransaction() {};
    void Clear() {};
    int GetSize() {};
    // Для фиксирования транзакций в файлах
    virtual void FixTransaction(){};
};

class TransactionJournal : public ITransactionJournal<Transaction> {
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


class TestJournal : public ITransactionJournal<std::string> {
private:
    std::vector<std::string> list;
public:
    ~TestJournal() = default;

    void AddTransaction(std::string _tr) override {
        list.push_back(_tr);
    }
    int GetSize() {
        return list.size();
    }
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
