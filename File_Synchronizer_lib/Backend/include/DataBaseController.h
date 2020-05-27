#ifndef FILE_SYNCHRONIZER_DATABASECONTROLLER_H
#define FILE_SYNCHRONIZER_DATABASECONTROLLER_H

#include "DataBaseWrapper.h"
#include "FileWatcher.h"
#include "IMediator.h"

#include <chrono>
#include <memory>
#include <queue>
#include <thread>

namespace FileSynchronizer {
    class DataBaseController : virtual public IMediator,
                               virtual public std::enable_shared_from_this<DataBaseController> {
    public:
        explicit DataBaseController(fs::path configure_file_path, DataBaseWrapper& db);
        ~DataBaseController() override;

        void Notify(EventType event) override;
        void Start();
        void Stop();

        bool CheckEvents() const;
        EventType HandleEvent();

        std::shared_ptr<DataBaseController> GetPtr();

    private:
        fs::path configure_file_path;
        const std::string_view delim = ">>>>>>>>>>";

        std::unique_ptr<FileWatcher> file_watcher;
        DataBaseWrapper& db;

        std::queue<EventType> event_queue;

        void HandleFileChangedEvent();
    };
}

#endif //FILE_SYNCHRONIZER_DATABASECONTROLLER_H
