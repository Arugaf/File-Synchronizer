#include "ApplicationController.h"

#include <fstream>

using FileSynchronizer::ApplicationController;
namespace fs = std::filesystem;

ApplicationController::ApplicationController(const fs::path& working_path,
                                             const std::shared_ptr<DataBaseController>& controller,
                                             DataBaseWrapper& DB,
                                             VersionManagerWrapper& VM) : controller(controller),
                                                                          VM(VM),
                                                                          DB(DB) {
    config_file /= "configure.cfg";
    DB.LoadDBFromFile();
}

void ApplicationController::Start() {
    controller->Start();
    listener = std::thread(&ApplicationController::Listen, this);
}

void FileSynchronizer::ApplicationController::Listen() {
    while (working) {
        if (controller->CheckEvents()) {
            controller->HandleEvent();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void FileSynchronizer::ApplicationController::Stop() {
    working = false;
    if (listener.joinable()) {
        listener.join();
    }
    controller->Stop();
}

void FileSynchronizer::ApplicationController::AddDirectory(const fs::path& dir) {
    controller->Stop();
    controller->Start();

    //TODO
}

void FileSynchronizer::ApplicationController::DeleteDirectory(const fs::path& dir) {
    controller->Stop();
    controller->Start();

    //TODO
}

void FileSynchronizer::ApplicationController::AddIgnoredFile(const fs::path& file) {
    controller->Stop();
    controller->Start();

    //TODO
}

void FileSynchronizer::ApplicationController::DeleteIgnoredFile(const fs::path& file) {
    controller->Stop();
    controller->Start();

    //TODO
}

void FileSynchronizer::ApplicationController::ShowFilesList() {
    for (const auto& it : DB.GetAllFiles()) {
        std::cout << it.first << std::endl;
    }
}

void FileSynchronizer::ApplicationController::ShowFileVersions(const fs::path& file) {
    VM.ShowFileVersions(file);
}

void FileSynchronizer::ApplicationController::RestoreVersion(const fs::path& file, int index) {
    VM.RestoreFileVersion(file, index);
}

void FileSynchronizer::ApplicationController::ClearDB() {
    DB.ClearDB();
}

void FileSynchronizer::ApplicationController::ShowLog() {

}

void FileSynchronizer::ApplicationController::ShowLogHead(int count) {

}

void FileSynchronizer::ApplicationController::ShowLogTail(int count) {

}

void FileSynchronizer::ApplicationController::ShowLogData(const std::string& date) {

}

void FileSynchronizer::ApplicationController::ShowLogFile(const std::string& file) {

}

