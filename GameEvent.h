#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

struct GameEvent {
    std::string eventType;
    std::string timestamp;
    std::string message;

    GameEvent(const std::string& type, const std::string& msg)
        : eventType(type), message(msg) {
        
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S");
        timestamp = ss.str();
    }
};

#endif