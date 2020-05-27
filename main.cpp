#include <iostream>

#include "File_Synchronizer_lib/Backend/include/DataBaseController.h"
#include "File_Synchronizer_lib/Backend/include/CommandReader.h"
#include "File_Synchronizer_lib/LogParser/include/LogParser.h"

int main(int argc, char** argv) {

    std::cout << argv[1] << std::endl;

    FileSynchronizer::DataBaseWrapper db_w;

    auto controller = std::make_shared<FileSynchronizer::DataBaseController>(argv[1], db_w);
    controller->Start();

    FileSynchronizer::LogParser lp;
    lp.ShowLogHead(5);

    while (getc(stdin) != 'q') {
        if (controller->CheckEvents()) {
            controller->HandleEvent();
        }
    }

    controller->Stop();

    return 0;
}
