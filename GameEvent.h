#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class TimestampGenerator {
public:
    static std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time_t_now = std::chrono::system_clock::to_time_t(now);

        std::tm tm;
#ifdef _WIN32
        localtime_s(&tm, &time_t_now);
#else
        localtime_r(&time_t_now, &tm);
#endif

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
};

struct GameEvent {
    std::string eventType;
    std::string timestamp;
    std::string message;

    GameEvent(const std::string& type, const std::string& msg)
        : eventType(type), message(msg), timestamp(TimestampGenerator::getCurrentTimestamp()) {
    }

    GameEvent(const GameEvent&) = default;
    GameEvent& operator=(const GameEvent&) = default;
    GameEvent(GameEvent&&) = default;
    GameEvent& operator=(GameEvent&&) = default;
};

#endif // GAMEEVENT_H