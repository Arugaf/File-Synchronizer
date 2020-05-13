#ifndef FILE_SYNCHRONIZER_SYNCCONTROLLER_H
#define FILE_SYNCHRONIZER_SYNCCONTROLLER_H

#include "FileWatcher.hpp"
#include "IMediator.h"

#include <chrono>
#include <memory>
#include <queue>
#include <thread>

namespace FileSynchronizer {
    // TODO: контроллер входящих соединений, управление базой данных (обновление, запрос данных для версий, запрос транзакций), сбор данных для отправления, разрешение принятыых данных
    class SyncController : public IMediator {
    public:
        explicit
        SyncController(std::string working_path, int delay_s = default_delay);
        ~SyncController();

        void Notify(EventType event) override;

        bool CheckEvents() const;
        EventType HandleEvent();

    private:
        static const int default_delay = 1;
        std::chrono::seconds delay_s;

        std::unique_ptr<FileWatcher> file_watcher;

        bool mutable listening = false;
        std::thread listener;
        std::queue<EventType> mutable event_queue;

        void HandleFileChangedEvent();
    };
}

#endif //FILE_SYNCHRONIZER_SYNCCONTROLLER_H
