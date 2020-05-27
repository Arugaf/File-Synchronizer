#ifndef FILE_SYNCHRONIZER_ILOGPARSER_H
#define FILE_SYNCHRONIZER_ILOGPARSER_H

#include <string>

namespace FileSynchronizer {
    class ILogParser {
    public:
        virtual void ShowLogHead(int count) = 0;
        virtual void ShowLogTail(int count) = 0;
        virtual void ShowLogData(const std::string& date) = 0;
        virtual void ShowLogFile(const std::string& date) = 0;
        virtual ~ILogParser() = default;
    };
}

#endif //FILE_SYNCHRONIZER_ILOGPARSER_H
