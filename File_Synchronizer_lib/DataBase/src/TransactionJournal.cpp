#include "TransactionJournal.h"

TransactionJournal::TransactionJournal(const std::filesystem::path &source) {
    writer = new Writer();
    writer->InitFileForWriting(source);
    currentLevel = LogOperationsLevel::All;
}

TransactionJournal::~TransactionJournal() {
    delete writer;
    writer = nullptr;
}

void TransactionJournal::AddTransaction(Transaction transaction) {
    switch (currentLevel) {
        case LogOperationsLevel::CreateOnly:
            if (transaction.operation == Operation::created) {
                transactionList.push_back(transaction);
            }
            break;
        case LogOperationsLevel::DeleteOnly:
            if (transaction.operation == Operation::deleted) {
                transactionList.push_back(transaction);
            }
            break;
        case LogOperationsLevel::ModifyOnly:
            if (transaction.operation == Operation::modified) {
                transactionList.push_back(transaction);
            }
            break;
        case LogOperationsLevel::CreateDelete:
            if (transaction.operation == Operation::created || transaction.operation == Operation::deleted) {
                transactionList.push_back(transaction);
            }
            break;
        case LogOperationsLevel::CreateModify:
            if (transaction.operation == Operation::created || transaction.operation == Operation::modified) {
                transactionList.push_back(transaction);
            }
            break;
        case LogOperationsLevel::DeleteModify:
            if (transaction.operation == Operation::deleted || transaction.operation == Operation::modified) {
                transactionList.push_back(transaction);
            }
            break;
        case LogOperationsLevel::All:
            transactionList.push_back(transaction);
            break;
    }
}

void TransactionJournal::FixTransaction() {
    for (auto &transaction : transactionList) {
        writer->Write(transaction);
    }
    Clear();
}

void TransactionJournal::SetLogOperationsLevel(LogOperationsLevel level) {
    currentLevel = level;
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

void TransactionJournal::SetTimeFormat(const std::string &_format) {
    writer->SetTimeFormat(_format);
}
