#ifndef FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
#define FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H

#include <filesystem>
#include <utility>
#include <vector>

#include "Transaction.h"
#include "JournalWriter/Writer.h"

template <typename TransactionRecord>
class ITransactionJournal {
public:
    virtual void AddTransaction(TransactionRecord) = 0;
    // Для фиксирования транзакций в файлах
    virtual void FixTransaction(){};

    virtual TransactionRecord GetLastTransaction() {};
    virtual void DeleteLastTransaction() {};
    virtual void Clear() {};
    virtual int GetSize() {};
};
// ---------------------------------------------------------------------
class TransactionJournal : public ITransactionJournal<Transaction> {
private:
    Writer* writer;
    std::vector<Transaction> transactionList;
public:
    TransactionJournal(const std::filesystem::path& source);
    ~TransactionJournal();

    void AddTransaction(Transaction transaction) override;
    // Записать текущий журнал транзакций в файл journalPath и очистить
    void FixTransaction() override;
    void Clear() override;

    [[maybe_unused]] Transaction GetLastTransaction() override;
    [[maybe_unused]] void DeleteLastTransaction() override;
    [[maybe_unused]] int GetSize() override;
};
// ---------------------------------------------------------------------
class TestJournal : public ITransactionJournal<std::string> {
private:
    std::vector<std::string> list;
public:
    ~TestJournal() = default;

    [[maybe_unused]] void FixTransaction() override {};

    void AddTransaction(std::string _tr) override {
        list.push_back(_tr);
    }

    std::string GetLastTransaction() override {
        return list.back();
    }
    void DeleteLastTransaction() override {
        list.pop_back();
    }
    void Clear() override {
        list.clear();
    }
    int GetSize() override {
        return list.size();
    }
};

#endif //FILE_SYNCHRONIZER_TRANSACTIONJOURNAL_H
