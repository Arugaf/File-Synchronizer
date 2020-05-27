#ifndef FILE_SYNCHRONIZER_COMMANDREADER_H
#define FILE_SYNCHRONIZER_COMMANDREADER_H

#include "ApplicationController.h"

namespace FileSynchronizer {
    class CommandReader {
    public:
        explicit CommandReader(ApplicationController& controller);

    private:
        void Listen();
        static void Help();
        ApplicationController& controller;
    };
}

#endif //FILE_SYNCHRONIZER_COMMANDREADER_H
