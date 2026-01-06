#ifndef IGAMEEVENTOBSERVER_H
#define IGAMEEVENTOBSERVER_H

#include "GameEvent.h"

class IGameEventObserver {
public:
    virtual ~IGameEventObserver() = default;
    virtual void onEventOccurred(const GameEvent& event) = 0;
};

#endif // IGAMEEVENTOBSERVER_H