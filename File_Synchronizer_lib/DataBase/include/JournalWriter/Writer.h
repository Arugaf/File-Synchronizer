#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITER_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITER_H_

#include <filesystem>
#include "Transaction.h"

class WriterImpl;

class Writer {
private:
    std::string defaultTimeFormat = "%d %B %Y %T";

    WriterImpl* writerImpl;
public:
    Writer();
    virtual ~Writer();

    void InitFileForWriting(const std::filesystem::path &source);

    // Изменить формат времени
    // по умолчанию: день.месяц.год часы(24ч):минуты:секунды = %d.%B.%Y %T
    void SetTimeFormat(const std::string &_format);

    void Write(const Transaction &transaction);
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_JOURNALWRITER_WRITER_H_
