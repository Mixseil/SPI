#include <iostream>
#include <memory>
#include "ServerConfig.h"
#include "ServerBuilder.h"

int main() {

    // Пример 1: Создание конфигурации с помощью fluent API

    ServerConfig config1 = ServerBuilder()
        .setPort(9000)
        .setReadTimeout(30)
        .enableLogging()
        .setMaxHeaderKB(2048)  // 2KB
        .enableTLS()
        .build();

    config1.display();

    // Пример 2: Другая комбинация параметров

    ServerConfig config2 = ServerBuilder()
        .setPort(8080)
        .setReadTimeout(10)
        .setWriteTimeout(20)
        .disableLogging()
        .setMaxHeaderMB(5)  // 5MB
        .disableTLS()
        .build();

    config2.display();

    // Пример 3: Только часть параметров (остальные по умолчанию)

    ServerConfig config3 = ServerBuilder()
        .setPort(3000)
        .enableLogging()
        .build();

    config3.display();

    // Пример 4: Использование статических фабричных методов

    std::cout << "\nProduction Configuration" << std::endl;
    ServerConfig productionConfig = ServerBuilder::createProductionConfig();
    productionConfig.display();

    std::cout << "\nDevelopment Configuration" << std::endl;
    ServerConfig devConfig = ServerBuilder::createDevelopmentConfig();
    devConfig.display();

    std::cout << "\nDefault Configuration" << std::endl;
    ServerConfig defaultConfig = ServerBuilder::createDefaultConfig();
    defaultConfig.display();

    // Пример 5: Демонстрация того, что Builder можно переиспользовать

    ServerBuilder builder;

    // Первая конфигурация
    ServerConfig cfg1 = builder
        .setPort(8001)
        .setReadTimeout(25)
        .enableLogging()
        .build();
    cfg1.display();

    // Сбросим builder и создадим другую конфигурацию
    ServerBuilder builder2;  

    ServerConfig cfg2 = builder2
        .setPort(8002)
        .enableTLS()
        .setMaxHeaderMB(3)
        .build();
    cfg2.display();

    // Пример 6: Валидация (демонстрация проверки значений)
    try {
        ServerConfig invalidConfig = ServerBuilder()
            .setPort(-1)  // Некорректный порт
            .build();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    return 0;
}