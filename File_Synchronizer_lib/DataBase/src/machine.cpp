#include "machine.h"

void Machine::SetId(const int &id_machine) {
    id = id_machine;
}
int Machine::GetId() {
    return id;
}

std::vector<File> Machine::GetSyncFilesListForMachine() {
    return syncFiles;
}

int Machine::GetCountSyncFilesForMachine() {
    return syncFiles.size();
}

void Machine::AddFileForSync(const File &file) {
    syncFiles.push_back(file);
}

void Machine::DeleteFileForSync(const File &file) {
    syncFiles.erase(std::remove(syncFiles.begin(), syncFiles.end(), file), syncFiles.end());
}

void Machine::ClearSyncFiles() {
    syncFiles.clear();
}

void Machine::Print(std::ostream &out) {
    std::string info;

    info = std::to_string(id) + "\n";

    for (auto item : syncFiles) {
        info += item.GetFilepath().string();
        info += " ";
    }

    out << info;
}

// что то сделать с syncList, getMachineFromFileinfo()