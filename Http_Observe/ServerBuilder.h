#ifndef SERVERBUILDER_H
#define SERVERBUILDER_H

#include "ServerConfig.h"
#include <iostream>

class ServerBuilder {
private:
    ServerConfig config;

public:
    ServerBuilder() {
        std::cout << "[ServerBuilder] Initialized with default configuration" << std::endl;
        std::cout << "  Default Port: " << config.getPort() << std::endl;
        std::cout << "  Default Read Timeout: " << config.getReadTimeout() << "s" << std::endl;
        std::cout << "  Default Write Timeout: " << config.getWriteTimeout() << "s" << std::endl;
        std::cout << "  Default Logging: " << (config.isLoggingEnabled() ? "Enabled" : "Disabled") << std::endl;
        std::cout << "  Default Max Header Size: " << config.getMaxHeaderBytes() << " bytes" << std::endl;
        std::cout << "  Default TLS: " << (config.isTLSEnabled() ? "Enabled" : "Disabled") << std::endl;
        std::cout << std::endl;
    }

    ServerBuilder& setPort(int port) {
        config.setPort(port);
        std::cout << "[ServerBuilder] Configured Port: " << port << std::endl;
        return *this;
    }

    ServerBuilder& setReadTimeout(int seconds) {
        config.setReadTimeout(seconds);
        std::cout << "[ServerBuilder] Configured Read Timeout: " << seconds << " seconds" << std::endl;
        return *this;
    }

    ServerBuilder& setWriteTimeout(int seconds) {
        config.setWriteTimeout(seconds);
        std::cout << "[ServerBuilder] Configured Write Timeout: " << seconds << " seconds" << std::endl;
        return *this;
    }

    ServerBuilder& enableLogging() {
        config.setEnableLogging(true);
        std::cout << "[ServerBuilder] Enabled Logging" << std::endl;
        return *this;
    }

    ServerBuilder& disableLogging() {
        config.setEnableLogging(false);
        std::cout << "[ServerBuilder] Disabled Logging" << std::endl;
        return *this;
    }

    ServerBuilder& setMaxHeaderBytes(int bytes) {
        config.setMaxHeaderBytes(bytes);
        std::cout << "[ServerBuilder] Configured Max Header Size: " << bytes << " bytes" << std::endl;
        return *this;
    }

    ServerBuilder& setMaxHeaderKB(int kb) {
        int bytes = kb * 1024;
        return setMaxHeaderBytes(bytes);
    }

    ServerBuilder& setMaxHeaderMB(int mb) {
        int bytes = mb * 1024 * 1024;
        return setMaxHeaderBytes(bytes);
    }

    ServerBuilder& enableTLS() {
        config.setTLSEnabled(true);
        std::cout << "[ServerBuilder] Enabled TLS" << std::endl;
        return *this;
    }

    ServerBuilder& disableTLS() {
        config.setTLSEnabled(false);
        std::cout << "[ServerBuilder] Disabled TLS" << std::endl;
        return *this;
    }

    ServerConfig build() {
        std::cout << "[ServerBuilder] Building final configuration..." << std::endl;
        std::cout << "Final Config: " << config.toString() << std::endl;
        return config;
    }

    static ServerConfig createDefaultConfig() {
        return ServerBuilder().build();
    }

    static ServerConfig createProductionConfig() {
        return ServerBuilder()
            .setPort(443)
            .setReadTimeout(30)
            .setWriteTimeout(30)
            .enableLogging()
            .setMaxHeaderMB(2)
            .enableTLS()
            .build();
    }

    static ServerConfig createDevelopmentConfig() {
        return ServerBuilder()
            .setPort(3000)
            .setReadTimeout(60)
            .setWriteTimeout(60)
            .enableLogging()
            .setMaxHeaderMB(10)
            .disableTLS()
            .build();
    }
};

#endif // SERVERBUILDER_H