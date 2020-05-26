#include "transactionjournal.h"

#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

void TransactionJournal::AddTransaction(Transaction transaction) {
    transactionList.push_back(transaction);
}

void TransactionJournal::Clear() {
    transactionList.clear();

    FixJournal();
}

int TransactionJournal::GetJournalSize() {
    return transactionList.size();
}

void TransactionJournal::FixJournal() {
    boost::property_tree::ptree root;

    boost::property_tree::ptree list;
    for (auto &transaction : transactionList) {
        boost::property_tree::ptree transactionNode;
        auto readable_time = std::chrono::system_clock::to_time_t(transaction.lastOperationTime);

        transactionNode.put("file", transaction.target.string());
        transactionNode.put("time", std::asctime(std::localtime(&readable_time)));
        transactionNode.put("operation", to_string(transaction.operation));

        list.push_back(std::make_pair("", transactionNode));
    }
    root.add_child("journal", list);

    boost::property_tree::write_json(journalPath, root);
}



