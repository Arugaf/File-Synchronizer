#include "JournalWriter/Writer.h"
#include "JournalWriter/WriterImpl.h"

#ifndef WRITER_IMPL
    #include "JournalWriter/WriterJSON.h"
    #define WRITER_IMPL WriterJSON
#endif


Writer::Writer() {
    writerImpl = new WRITER_IMPL();
    writerImpl->SetTimeFormat(defaultTimeFormat);
}

Writer::~Writer() {
    delete writerImpl;
    writerImpl = nullptr;
}

void Writer::InitFileForWriting(const std::filesystem::path &source) {
    writerImpl->InitFileForWriting(source);
}

void Writer::SetTimeFormat(const std::string &_format) {
    writerImpl->SetTimeFormat(_format);
}

void Writer::Write(const Transaction &transaction) {
    writerImpl->Write(transaction);
}



