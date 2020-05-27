#include "ApplicationController.h"

#include <fstream>

using FileSynchronizer::ApplicationController;
using FileSynchronizer::EventType;

ApplicationController::ApplicationController(const fs::path& working_path) : event_queue(), working_path(working_path) {
    std::fstream configure_file(working_path);
    fs::path path_to_watch;
    configure_file >> path_to_watch;

    try {
        file_watcher = std::make_unique<FileWatcher>(path_to_watch);
    } catch (FileSynchronizer::FileWatcherException::Exception& error) {
        std::cerr << error.what() << std::endl;
    }
}

ApplicationController::~ApplicationController() {
    file_watcher->StopWatching();
}

void ApplicationController::Notify(EventType event) {
    event_queue.push(event);
}

bool ApplicationController::CheckEvents() const {
    return !event_queue.empty();
}

void ApplicationController::HandleFileChangedEvent() {
    // TODO: Заглушка...
    for (const auto& it : file_watcher->GetChangedFiles()) {
        std::cout << it.first << ' ';
        switch (it.second) {
            case FileStatus::Created: {
                std::cout << "created" << std::endl;
                break;
            }
            case FileStatus::Modified: {
                std::cout << "modified" << std::endl;
                break;
            }
            case FileStatus::Deleted: {
                std::cout << "deleted" << std::endl;
                break;
            }
        }
    }
    file_watcher->ContinueWatching();
}

EventType ApplicationController::HandleEvent() {
    auto event = event_queue.front();
    switch (event) {
        case EventType::FSChanged: {
            HandleFileChangedEvent();
            break;
        }
    }
}

void ApplicationController::Start() {
    file_watcher->StartWatching(GetPtr());
}

std::shared_ptr<ApplicationController> ApplicationController::GetPtr() {
    return shared_from_this();
}

void FileSynchronizer::ApplicationController::Stop() {
    file_watcher->StopWatching();
}
