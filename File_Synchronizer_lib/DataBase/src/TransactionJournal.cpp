#include "TransactionJournal.h"

#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

void TransactionJournal::AddTransaction(Transaction transaction) {
    transactionList.push_back(transaction);
}

void TransactionJournal::FixTransaction() {
    boost::property_tree::ptree root;

    for (auto &transaction : transactionList) {
        boost::property_tree::ptree transactionNode;
        auto readable_time = std::chrono::system_clock::to_time_t(transaction.lastOperationTime);

        transactionNode.put("file", transaction.target.string());
        transactionNode.put("time", std::asctime(std::localtime(&readable_time)));
        transactionNode.put("operation", ConvertToString(transaction.operation));

        root.add_child("transaction", transactionNode);
    }

    std::ofstream out(journalPath, std::ios::app);
    boost::property_tree::write_json(out, root);
    out.close();
    transactionList.clear();
}



