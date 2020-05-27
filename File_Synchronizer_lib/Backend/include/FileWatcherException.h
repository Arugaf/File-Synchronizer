#ifndef FILE_SYNCHRONIZER_FILEWATCHEREXCEPTION_H
#define FILE_SYNCHRONIZER_FILEWATCHEREXCEPTION_H

#include <stdexcept>

namespace FileSynchronizer::FileWatcherException {
        class Exception : public std::runtime_error {
        public:
            explicit Exception(const std::string& msg);
        };

        class InvalidPath : public Exception {
        public:
            InvalidPath();
            explicit InvalidPath(const std::string& path);
        };
    }

#endif //FILE_SYNCHRONIZER_FILEWATCHEREXCEPTION_H
