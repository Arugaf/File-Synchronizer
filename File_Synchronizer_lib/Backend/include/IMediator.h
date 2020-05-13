//
// Created by arugaf on 11.05.2020.
//

#ifndef FILE_SYNCHRONIZER_IMEDIATOR_H
#define FILE_SYNCHRONIZER_IMEDIATOR_H

namespace FileSynchronizer {
    enum class EventType {
        FSChanged,
        ConnectionReceived
    };

    class IMediator {
    public:
        virtual void Notify(EventType) = 0;
        virtual ~IMediator() = default;
    };
}

#endif //FILE_SYNCHRONIZER_IMEDIATOR_H
