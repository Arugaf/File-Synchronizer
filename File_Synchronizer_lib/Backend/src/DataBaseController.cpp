#include "DataBaseController.h"

#include <fstream>
#include <utility>

using FileSynchronizer::DataBaseController;
using FileSynchronizer::EventType;

DataBaseController::DataBaseController(fs::path configure_file_path, DataBaseWrapper& db) :
db(db), event_queue(), configure_file_path(std::move(configure_file_path)) {

}

DataBaseController::~DataBaseController() {
    file_watcher->StopWatching();
}

void DataBaseController::Notify(EventType event) {
    event_queue.push(event);
}

bool DataBaseController::CheckEvents() const {
    return !event_queue.empty();
}

void DataBaseController::HandleFileChangedEvent() {
    for (const auto& it : file_watcher->GetChangedFiles()) {
        std::string_view file_name(it.first);

        std::cout << file_name << ' ';
        switch (it.second) {
            case FileStatus::Created: {
                //std::cout << "created" << std::endl;
                db.HandleFileCreation(file_name);
                break;
            }
            case FileStatus::Modified: {
                //std::cout << "modified" << std::endl;
                db.HandleFileModification(file_name);
                break;
            }
            case FileStatus::Deleted: {
                //std::cout << "deleted" << std::endl;
                db.HandleFileDeletion(file_name);
                break;
            }
        }
    }
    db.SaveDbToFile();
    file_watcher->ContinueWatching();
}

EventType DataBaseController::HandleEvent() {
    auto event = event_queue.front();
    switch (event) {
        case EventType::FSChanged: {
            HandleFileChangedEvent();
            break;
        }
    }
    return event;
}

void DataBaseController::Start() {
    FilesInfo previous_files;

    if (!db.GetAllFiles().empty()) {
        for (const auto& file : db  .GetAllFiles()) {
            previous_files[file.first] = {file.second};
        }
    }

    std::ifstream configure_file(configure_file_path);

    path_list paths_to_watch;
    std::string path_to_watch;

    while (std::getline(configure_file, path_to_watch)) {
        if (path_to_watch == delim) {
            break;
        }
        paths_to_watch.emplace(path_to_watch);
    }

    FileNames ignored_files;

    while (std::getline(configure_file, path_to_watch)) {
        ignored_files.Insert(path_to_watch);
    }

    try {
        if (previous_files.empty()) {
            if (ignored_files.IsEmpty()) {
                file_watcher = std::make_unique<FileWatcher>(paths_to_watch);
            } else {
                file_watcher = std::make_unique<FileWatcher>(paths_to_watch, std::move(ignored_files));
            }
        } else {
            if (ignored_files.IsEmpty()) {
                file_watcher = std::make_unique<FileWatcher>(paths_to_watch, previous_files);
            } else {
                file_watcher = std::make_unique<FileWatcher>(paths_to_watch, std::move(ignored_files), previous_files);
            }
        }
    } catch (FileSynchronizer::FileWatcherException::Exception& error) {
        std::cerr << error.what() << std::endl;
    }

    file_watcher->StartWatching(GetPtr());
}

std::shared_ptr<DataBaseController> DataBaseController::GetPtr() {
    return shared_from_this();
}

void FileSynchronizer::DataBaseController::Stop() {
    file_watcher->StopWatching();
}
