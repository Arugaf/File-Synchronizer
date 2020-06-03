#include "JournalWriter/WriterJSON.h"

std::string_view WriterJSON::OperationToString(Operation operation) {
    switch (operation) {
        case Operation::created: return "created";
        case Operation::deleted: return "deleted";
        case Operation::modified: return "modified";
    }
}

const char* WriterJSON::LevelToString(groupLevel level) {
    switch (level) {
        case groupLevel::day : return "%d-%m-%Y";
        case groupLevel::month: return "%m-%Y";
        case groupLevel::year: return "%Y";
    }
}
// --------------------------------------------------------------------------------
template <class Tuple, size_t... I>
void WriterJSON::SplitTransactionTuple(const Tuple &t, std::index_sequence<I...>, boost::property_tree::ptree &_node) {
    //#define NAME(VAR) #VAR

    boost::property_tree::ptree parameter;
    (..., ( parameter.put("", std::get<I>(t)),
            _node.push_back(std::make_pair("", parameter))
            ) );

}
template <class...T>
void WriterJSON::CreateNode(const std::tuple<T...> &t, boost::property_tree::ptree &_node) {
    SplitTransactionTuple(t, std::make_index_sequence<sizeof...(T)>(), _node);
}
// --------------------------------------------------------------------------------
template <>
void WriterJSON::CreateNode<Transaction::path, Transaction::timePoint, Operation>(const std::tuple<Transaction::path, Transaction::timePoint, Operation> &t, boost::property_tree::ptree &_node) {
    boost::property_tree::ptree parameter;
    parameter.put("", std::get<0>(t).string());
    _node.push_back(std::make_pair("", parameter));

    parameter.put("", std::put_time(ConvertTime(std::get<1>(t)), timeFormat.c_str()));
    _node.push_back(std::make_pair("", parameter));

    parameter.put("", OperationToString(std::get<2>(t)));
    _node.push_back(std::make_pair("", parameter));
}
// --------------------------------------------------------------------------------
void WriterJSON::InitFileForWriting(const std::filesystem::path &source) {
    logFile = source / "journal.json";
}

void WriterJSON::SetTimeFormat(const std::string &_format) {
    timeFormat = _format;
}

tm* WriterJSON::ConvertTime(std::chrono::system_clock::time_point timepoint) {
    auto readableTime = std::chrono::system_clock::to_time_t(timepoint);
    return std::localtime(&readableTime);
}

void WriterJSON::Write(const Transaction &transaction) {
    boost::property_tree::ptree root;

    boost::property_tree::ptree node;
    CreateNode(transaction.GetRecord(), node);

    char buf[80];
    strftime(buf, 80, LevelToString(currentLogLevel), ConvertTime(std::chrono::system_clock::now()));

    root.add_child(buf, node);

    std::ofstream out(logFile, std::ios::app);
    boost::property_tree::write_json(out, root);
    out.close();
}
