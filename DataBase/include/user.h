#ifndef FILE_SYNCHRONIZER_USER_H
#define FILE_SYNCHRONIZER_USER_H

#include <string>
#include <vector>
#include <map>
#include <stack>

#include "versionmanager.h"
#include "transactionjournal.h"

class User {
private:
    std::string username;
    std::vector<int> connected_machines;
    std::map<std::string, bool> files_blacklist;

    std::map<std::string, std::vector<int>> files_to_machines;

public:
    User() {};
    explicit User(const std::string& user): username(user) {};
    ~User() = default;

    void set_username(const std::string& user);
    std::string get_username();

    // ----------- MACHINE MANAGE SECTION -------------------------------------
    std::vector<int> get_connected_machines();
    void AddConnectedMachine(const int& id_machine);
    void AddConnectedMachine(const std::vector<int>& machines);
    void DeleteConnectedMachine(const int& machine_id);

    // ----------- BLACKLIST SECTION -----------------------------------------
    void AddFileToBlacklist(const std::string& filename);
    void DeleteFileFromBlacklist(const std::string& filename);

    // ----------- SYNC LIST SECTION ------------------------------------------
    auto GetFullSyncMachinesListForFiles();
    std::vector<int> GetSyncMachinesListByFilename(const std::string& filename);
    int GetCountSyncMachinesForFile(const std::string& filename);

    // ----------- ADDING SECTION ----------------------------------------------
    // TODO: При добавлении файла добавить запись про него в Мета-класс? Мета класс??
    // добавит в список файл-машины, файл-блеклист, создать аналогичную функцию наверное в машине,
    // которая будет создавать папку для нового файла
    void AddFileForSync(const std::string& filename);
    void AddFileForSync(const std::string& filename, const std::vector<int>& machines);

    void AddMachineToFileForSync(const std::string& filename, const int& id_machine);
    void AddMachineToFileForSync(const std::string& filename, const std::vector<int>& machines);
    void AddMachineForSync(const int& id_machine);

    // ----------- DELETING SECTION ----------------------------------------------
    void DeleteSyncFile(const std::string& filename);
    void DeleteMachineForSyncFromFile(const std::string& filename, const int& id_machine);
    void ClearMachinesForSyncFromFile(const std::string& filename);

};

#endif //FILE_SYNCHRONIZER_USER_H
