#include "FileWatcherException.h"

FileSynchronizer::FileWatcherException::Exception::Exception(const std::string& msg) : std::runtime_error(msg) {

}

FileSynchronizer::FileWatcherException::InvalidPath::InvalidPath() : Exception("Invalid path") {

}

FileSynchronizer::FileWatcherException::InvalidPath::InvalidPath(const std::string& path) :
Exception("Invalid path: " + path) {

}
