#include "machine.h"

void Machine::SetId(const int &id_machine) {
    id = id_machine;
}
int Machine::GetId() {
    return id;
}

std::unordered_set<std::filesystem::path, std::hash<std::string>> Machine::GetSyncFilesListForMachine() {
    return syncFiles;
}

int Machine::GetCountSyncFilesForMachine() {
    return syncFiles.size();
}

void Machine::AddFileForSync(File file) {
    syncFiles.insert(file.GetFilepath());
}

void Machine::AddFileForSync(const std::filesystem::path &file) {
    syncFiles.insert(file);
}

void Machine::DeleteFileForSync(File file) {
    syncFiles.erase(file.GetFilepath());
}

void Machine::DeleteFileForSync(const std::filesystem::path &file) {
    syncFiles.erase(file);
}

void Machine::ClearSyncFiles() {
    syncFiles.clear();
}

void Machine::Print(std::ostream &out) {
    std::string info;

    info = std::to_string(id) + "\n";

    for (auto item : syncFiles) {
        info += item.string();
        info += " ";
    }

    out << info;
}


