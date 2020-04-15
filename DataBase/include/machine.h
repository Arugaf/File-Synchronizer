#ifndef FILE_SYNCHRONIZER_MACHINE_H
#define FILE_SYNCHRONIZER_MACHINE_H


#include <string>
#include <vector>
#include <map>
#include <filesystem>

#include "versionmanager.h"
#include "transactionjournal.h"
#include "usermanager.h"



class Machine {
private:
    int id;
    std::filesystem::path db_path;

    VersionHistoryManager _local_history_manager;
    TransactionJournal _transaction_journal;
    UserManager _user_manager;

public:
    Machine() {};
    Machine(int id_machine): id(id_machine) {};
    Machine(std::filesystem::path source): db_path(source) {};
    Machine(int id_machine, std::filesystem::path source): id(id_machine), db_path(source) {};
    ~Machine() {};


    int get_machine_id();
    void set_machine_id(const int& id_machine);

    std::filesystem::path get_db_path();
    void set_db_path(const std::filesystem::path& source);

    // -----------------------------------------------------------------------------
    int CreateDBDirectories();
    int DeleteDBDirectories();
    // -----------------------------------------------------------------------------
    int CreateDirectoryForFile(const std::string& filename);
    int DeleteDirectoryForFile(const std::string& filename);

};

#endif //FILE_SYNCHRONIZER_MACHINE_H
