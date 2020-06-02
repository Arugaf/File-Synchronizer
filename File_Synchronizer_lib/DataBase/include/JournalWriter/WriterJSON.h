#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITERJSON_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITERJSON_H_

#include <filesystem>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/type_index.hpp>

#include "JournalWriter/WriterImpl.h"

enum class groupLevel {
    day,
    month,
    year
};

class WriterJSON : public WriterImpl {
private:
    std::string timeFormat;
    groupLevel currentLogLevel;

    std::filesystem::path logFile;

    std::string_view OperationToString(Operation operation);
    const char* LevelToString(groupLevel level);
    template <class Tuple, size_t... I> void SplitTransactionTuple(const Tuple &t, std::index_sequence<I...>, boost::property_tree::ptree &_node);
    template <class...T> void CreateNode(const std::tuple<T...> &t, boost::property_tree::ptree &_node);
public:
    WriterJSON(): currentLogLevel(groupLevel::month) {};
    WriterJSON(const groupLevel &level): currentLogLevel(level) {};
    ~WriterJSON() override = default;

    void InitFileForWriting(const std::filesystem::path &source) override;

    void SetTimeFormat(const std::string &_format) override;
    tm* ConvertTime(std::chrono::system_clock::time_point timepoint) override;

    void Write(const Transaction &transaction) override;
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITERJSON_H_
