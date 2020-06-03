#ifndef FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_FILEEXCEPTION_H_
#define FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_FILEEXCEPTION_H_

#include <filesystem>

struct FileSearchException : public std::exception {
    [[nodiscard]] const char * what () const noexcept override {
        return "File doesn't exist";
    }
};

#endif //FILE_SYNCHRONIZER_FILE_SYNCHRONIZER_LIB_DATABASE_INCLUDE_FILEEXCEPTION_H_
