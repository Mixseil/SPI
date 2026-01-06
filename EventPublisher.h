#ifndef EVENTPUBLISHER_H
#define EVENTPUBLISHER_H

#include "IGameEventObserver.h"
#include <vector>
#include <algorithm>
#include <memory>

class EventPublisher {
private:
    std::vector<IGameEventObserver*> observers;

public:
    void subscribe(IGameEventObserver* observer) {
        if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }

    void unsubscribe(IGameEventObserver* observer) {
        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyAll(const GameEvent& event) {
        for (auto observer : observers) {
            observer->onEventOccurred(event);
        }
    }

    size_t getObserverCount() const {
        return observers.size();
    }
};

#endif // EVENTPUBLISHER_H