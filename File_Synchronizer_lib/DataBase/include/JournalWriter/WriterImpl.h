#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITERIMPL_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITERIMPL_H_

#include <filesystem>
#include "Transaction.h"

class WriterImpl {
public:
    WriterImpl() = default;
    virtual ~WriterImpl() = default;

    virtual void InitFileForWriting(const std::filesystem::path &source) = 0;

    virtual void SetTimeFormat(const std::string &_format) = 0;
    virtual tm* ConvertTime(std::chrono::system_clock::time_point timepoint) = 0;

    virtual void Write(const Transaction &transaction) = 0;
};


#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITERIMPL_H_
