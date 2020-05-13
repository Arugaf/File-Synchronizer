#include "SyncController.h"

FileSynchronizer::SyncController::
SyncController(std::string path_to_watch, int delay_s) : event_queue(), delay_s(delay_s) {
    try {
        file_watcher = std::make_unique<FileWatcher>(std::move(path_to_watch));
        file_watcher->StartWatching(this);
    } catch (FileSynchronizer::FileWatcherException::Exception& error) {
        std::cerr << error.what() << std::endl;
    }
}

FileSynchronizer::SyncController::
~SyncController() {
    file_watcher->StopWatching();
}

void
FileSynchronizer::SyncController::
Notify(FileSynchronizer::EventType event) {
    event_queue.push(event);
}

bool
FileSynchronizer::SyncController::
CheckEvents() const {
    return !event_queue.empty();
}

void
FileSynchronizer::SyncController::
HandleFileChangedEvent() {
    // TODO: Заглушка...
    for (const auto& it : file_watcher->GetChangedFiles()) {
        std::cout << it.first << ' ';
        switch (it.second) {
            case FileStatus::Created: {
                std::cout << "created" << std::endl;
                break;
            }
            case FileStatus::Changed: {
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

FileSynchronizer::EventType
FileSynchronizer::SyncController::
HandleEvent() {
    auto event = event_queue.front();
    switch (event) {
        case EventType::FSChanged: {
            HandleFileChangedEvent();
            break;
        }

        case EventType::ConnectionReceived: {
            break;
        }
    }
}
