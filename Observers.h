#ifndef OBSERVERS_H
#define OBSERVERS_H

#include "IGameEventObserver.h"
#include <iostream>

class LoggerObserver : public IGameEventObserver {
public:
    void onEventOccurred(const GameEvent& event) override {
        std::cout << "[LOG] Event: " << event.message
            << " (Type: " << event.eventType
            << ", Time: " << event.timestamp << ")" << std::endl;
    }
};

class StatsObserver : public IGameEventObserver {
private:
    int eventCount = 0;

public:
    void onEventOccurred(const GameEvent& event) override {
        eventCount++;
        std::cout << "[STATS] Total events: " << eventCount
            << " | Current: " << event.eventType << std::endl;
    }

    int getTotalEvents() const {
        return eventCount;
    }
};

class UIObserver : public IGameEventObserver {
public:
    void onEventOccurred(const GameEvent& event) override {
        std::cout << "[UI] Updating display for: " << event.message
            << " (" << event.eventType << ")" << std::endl;
    }
};

#endif // OBSERVERS_H