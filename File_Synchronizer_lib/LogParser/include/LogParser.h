#ifndef FILE_SYNCHRONIZER_LOGPARSER_H
#define FILE_SYNCHRONIZER_LOGPARSER_H

#include "ILogParser.h"

#include <iostream>

namespace FileSynchronizer {
    class LogParser : public ILogParser {
    public:
        void ShowLogHead(int count) override;
        void ShowLogTail(int count) override {};
        void ShowLogData(const std::string& date) override {};
        void ShowLogFile(const std::string& date) override {};
    };
}

#endif //FILE_SYNCHRONIZER_LOGPARSER_H
