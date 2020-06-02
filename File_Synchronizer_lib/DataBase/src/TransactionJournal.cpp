#include "TransactionJournal.h"

TransactionJournal::TransactionJournal(const std::filesystem::path &source) {
    writer = new Writer();
    writer->InitFileForWriting(source);
}

TransactionJournal::~TransactionJournal() {
    delete writer;
    writer = nullptr;
}

void TransactionJournal::AddTransaction(Transaction transaction) {
    transactionList.push_back(transaction);
}

void TransactionJournal::FixTransaction() {
    for (auto &transaction : transactionList) {
        writer->Write(transaction);
    }
    Clear();
}

void TransactionJournal::DeleteLastTransaction()  {
    transactionList.pop_back();
}

Transaction TransactionJournal::GetLastTransaction() {
    return transactionList.back();
}

void TransactionJournal::Clear() {
    transactionList.clear();
}

int TransactionJournal::GetSize() {
    return transactionList.size();
}
