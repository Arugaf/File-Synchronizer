//
// Created by Administrator on 14.04.2020.
//

#ifndef UNTITLED9_TRANSACTIONJOURNAL_H
#define UNTITLED9_TRANSACTIONJOURNAL_H

#include <string>
#include <filesystem>


class TransactionJournal {
private:
    std::filesystem::path transaction_path;
    int current_machine_transaction;
public:
    std::filesystem::path get_transaction_path();
    void set_transaction_path(const std::filesystem::path& source);

    void set_current_machine_transaction(const int& transaction_num);
    int get_current_machine_transaction();

    void CreateTransaction(const std::string& operation_type, const std::string& filename);

    int ClearTransactions();

    std::filesystem::path GetTransactionJournal();

};


#endif //UNTITLED9_TRANSACTIONJOURNAL_H
