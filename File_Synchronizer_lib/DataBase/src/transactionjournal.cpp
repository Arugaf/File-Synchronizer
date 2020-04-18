#include "transactionjournal.h"

void TransactionJournal::set_journal_path(const fs::path &source) {

}

fs::path TransactionJournal::get_journal_path() {
    return fs::path();
}

std::vector<Transaction> TransactionJournal::get_transaction_list() {
    return std::vector<Transaction>();
}

void TransactionJournal::AddTransaction(const Transaction &transaction) {

}

void TransactionJournal::DeleteTransaction(const Transaction &transaction) {

}

void TransactionJournal::Clear() {

}

void TransactionJournal::FixJournal() {

}