#include <iostream>
#include <memory>

#include "File_Synchronizer_lib/Backend/include/ApplicationController.h"
#include "File_Synchronizer_lib/DataBase/include/FileManager.h"
#include "File_Synchronizer_lib/include/IFileManager.h"
#include "File_Synchronizer_lib/Backend/include/CommandReader.h"

#define DATABASE

int main(int argc, char** argv) {

    //std::cout << argv[1] << std::endl;

    auto file_manager = std::make_unique<FileManager>(argv[1]);
    FileSynchronizer::DataBaseWrapper database_wrapper(std::move(file_manager));

    std::filesystem::path configure_file = argv[1];
    configure_file /= "configure.cfg";
    auto db_controller = std::make_shared<FileSynchronizer::DataBaseController>(configure_file, database_wrapper);
    //FileSynchronizer::DataBaseController db_controller(configure_file, database_wrapper);

    auto versionManager = std::make_unique<VersionManager>(argv[1]);
    FileSynchronizer::VersionManagerWrapper vm_wrapper(std::move(versionManager));

    FileSynchronizer::ApplicationController application(argv[1], db_controller, database_wrapper, vm_wrapper);
    application.Start();
    // while (true);
    FileSynchronizer::CommandReader commandReader(application);


    //auto controller = std::make_shared<FileSynchronizer::DataBaseController>(argv[1], db_w);
    //controller->Start();

    //FileSynchronizer::LogParser lp;
    /*lp.ShowLogHead(5);

    while (getc(stdin) != 'q') {
        if (controller->CheckEvents()) {
            controller->HandleEvent();
        }
    }

    controller->Stop();*/

    return 0;
}
