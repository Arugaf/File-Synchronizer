//
// Created by arugaf on 15.04.2020.
//

#ifndef FILE_SYNCHRONIZER_SYNCH_CONTROLLER_H
#define FILE_SYNCHRONIZER_SYNCH_CONTROLLER_H

#include <filesystem>
#include <memory>
#include <vector>

namespace fs = std::filesystem;

class DataBase;
class LocalData;
class Connection;

namespace FileSynchronizer {
    class SynchController {
    public:
        static std::shared_ptr<SynchController> GetInstance(std::shared_ptr<DataBase> db, fs::path configure_file_path, int id);
        static std::shared_ptr<SynchController> GetInstance(std::shared_ptr<DataBase> db, fs::path configure_file_path);

        int HandleReceivingConnectionPull(const Connection& connection);
        int HandleReceivingConnectionSend(const Connection& connection);
        int HandleProvokingConnectionSend(const std::vector<Connection>& connections);
        int HandleProvokingConnectionPull(const std::vector<Connection>& connections);

        void NotifyFSChange();

        int Synchronize();
        int UpdateAfterStart();
        int GetAllData();

        std::shared_ptr<LocalData> GetLocalData();

    private:
        SynchController(std::shared_ptr<DataBase> db, fs::path configure_file_path, int id);
        SynchController(std::shared_ptr<DataBase> db, fs::path configure_file_path);

        static std::shared_ptr<SynchController> instance;

        std::shared_ptr<DataBase> data_base;
        std::shared_ptr<LocalData> local_data;
    };
} // FileSynchronizer namespace end

#endif //FILE_SYNCHRONIZER_SYNCH_CONTROLLER_H
