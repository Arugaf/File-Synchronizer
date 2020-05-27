#ifndef FILE_SYNCHRONIZER_IMEDIATOR_H
#define FILE_SYNCHRONIZER_IMEDIATOR_H

namespace FileSynchronizer {
    enum class EventType {
        FSChanged
    };

    class IMediator {
    public:
        virtual void Notify(EventType) = 0;
        virtual ~IMediator() = default;
    };
}

#endif //FILE_SYNCHRONIZER_IMEDIATOR_H
