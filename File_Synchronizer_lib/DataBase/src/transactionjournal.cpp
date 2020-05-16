#include "transactionjournal.h"

#include <fstream>

void TransactionJournal::SetJournalPath(const std::filesystem::path &source) {
    journalPath = source / "journal.txt";
    std::filesystem::create_directories(journalPath);
}

std::filesystem::path TransactionJournal::GetJournalPath() {
    return journalPath;
}

std::vector<Transaction> TransactionJournal::GetTransactionList() {
    return transactionList;
}

void TransactionJournal::AddTransaction(Transaction transaction) {
    transactionList.push_back(transaction);
    currentTransaction++;
}

void TransactionJournal::DeleteLastTransaction() {
    transactionList.pop_back();
    currentTransaction--;
}

void TransactionJournal::Clear() {
    transactionList.clear();
    currentTransaction = 0;

    FixJournal();
}

int TransactionJournal::GetJournalSize() {
    return transactionList.size();
}

void TransactionJournal::FixJournal() {
    std::ofstream file(journalPath);

    if (file.is_open()) {
        for (auto item : transactionList) {
            item.Print(file);
        }
    }
    // else throw bad_argument?
    file.close();
}


