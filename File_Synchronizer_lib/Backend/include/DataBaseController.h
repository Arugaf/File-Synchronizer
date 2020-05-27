#ifndef FILE_SYNCHRONIZER_APPLICATIONCONTROLLER_H
#define FILE_SYNCHRONIZER_APPLICATIONCONTROLLER_H

#include "FileWatcher.h"
#include "IMediator.h"

#include <chrono>
#include <memory>
#include <queue>
#include <thread>

namespace FileSynchronizer {
    class ApplicationController : virtual public IMediator,
                                  virtual public std::enable_shared_from_this<ApplicationController> {
    public:
        explicit ApplicationController(const fs::path& working_path);
        ~ApplicationController() override;

        void Notify(EventType event) override;
        void Start();
        void Stop();

        bool CheckEvents() const;
        EventType HandleEvent();

        std::shared_ptr<ApplicationController> GetPtr();

    private:
        fs::path working_path;

        std::unique_ptr<FileWatcher> file_watcher;

        std::queue<EventType> event_queue;

        void HandleFileChangedEvent();
    };
}

#endif //FILE_SYNCHRONIZER_APPLICATIONCONTROLLER_H
