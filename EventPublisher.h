#ifndef EVENTPUBLISHER_H
#define EVENTPUBLISHER_H

#include "IGameEventObserver.h"
#include <vector>
#include <algorithm>

class EventPublisher {
private:
    std::vector<IGameEventObserver*> observers;

public:
    void subscribe(IGameEventObserver* observer) {
        if (!observer) return; 

        if (std::find(observers.begin(), observers.end(), observer) == observers.end()) {
            observers.push_back(observer);
        }
    }

    void unsubscribe(IGameEventObserver* observer) {
        if (!observer) return; 

        auto it = std::find(observers.begin(), observers.end(), observer);
        if (it != observers.end()) {
            observers.erase(it);
        }
    }

    void notifyAll(const GameEvent& event) {
        for (auto observer : observers) {
            if (observer) {
                observer->onEventOccurred(event);
            }
        }
    }

    size_t getObserverCount() const {
        return observers.size();
    }
};

#endif // EVENTPUBLISHER_H