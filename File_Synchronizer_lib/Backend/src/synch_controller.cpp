//
// Created by arugaf on 15.04.2020.
//

#include "synch_controller.h"

std::shared_ptr<FileSynchronizer::SynchController>
FileSynchronizer::SynchController::GetInstance(std::shared_ptr<DataBase> db, fs::path configure_file_path, int id) {
    return std::shared_ptr<SynchController>();
}

std::shared_ptr<FileSynchronizer::SynchController>
FileSynchronizer::SynchController::GetInstance(std::shared_ptr<DataBase> db, fs::path configure_file_path) {
    return std::shared_ptr<SynchController>();
}

int FileSynchronizer::SynchController::HandleReceivingConnectionPull(const Connection& connection) {
    return 0;
}

int FileSynchronizer::SynchController::HandleReceivingConnectionSend(const Connection& connection) {
    return 0;
}

void FileSynchronizer::SynchController::NotifyFSChange() {

}

int FileSynchronizer::SynchController::Synchronize() {
    return 0;
}

FileSynchronizer::SynchController::SynchController(std::shared_ptr<DataBase> db, fs::path configure_file_path, int id) {

}

FileSynchronizer::SynchController::SynchController(std::shared_ptr<DataBase> db, fs::path configure_file_path) {

}

int FileSynchronizer::SynchController::HandleProvokingConnectionSend(const std::vector<Connection>& connections) {
    return 0;
}

int FileSynchronizer::SynchController::HandleProvokingConnectionPull(const std::vector<Connection>& connections) {
    return 0;
}

int FileSynchronizer::SynchController::UpdateAfterStart() {
    return 0;
}

int FileSynchronizer::SynchController::GetAllData() {
    return 0;
}

std::shared_ptr<LocalData> FileSynchronizer::SynchController::GetLocalData() {
    return std::shared_ptr<LocalData>();
}
