#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include "GameEvent.h"
#include "EventPublisher.h"
#include "Observers.h"

int main() {
    EventPublisher publisher;

    LoggerObserver logger;
    StatsObserver stats;
    UIObserver ui;

    publisher.subscribe(&logger);
    publisher.subscribe(&stats);
    publisher.subscribe(&ui);

    // Событие 1: Игрок получил урон
    GameEvent event1("PlayerDamaged", "Player took 10 damage from enemy");
    publisher.notifyAll(event1);
    std::cout << std::endl;

    // Событие 2: Собран предмет
    GameEvent event2("ItemCollected", "Player collected Health Potion");
    publisher.notifyAll(event2);
    std::cout << std::endl;

    // Событие 3: Пройден уровень
    GameEvent event3("LevelCompleted", "Player completed Level 3");
    publisher.notifyAll(event3);
    std::cout << std::endl;

    // Событие 4: Достижение разблокировано
    GameEvent event4("AchievementUnlocked", "Unlocked 'Treasure Hunter' achievement");
    publisher.notifyAll(event4);
    std::cout << std::endl;

    // Отписываем одного наблюдателя
    publisher.unsubscribe(&ui);

    // Генерируем еще одно событие
    GameEvent event5("PlayerLevelUp", "Player reached level 5");
    publisher.notifyAll(event5);
    return 0;
}