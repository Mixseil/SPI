#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <string>
#include <iostream>
#include <iomanip>
#include <stdexcept>

class InvalidConfigurationException : public std::runtime_error {
public:
    explicit InvalidConfigurationException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class ServerConfig {
private:
    int port = 8080;
    int readTimeout = 15;
    int writeTimeout = 15;
    bool enableLogging = false;
    int maxHeaderBytes = 1048576;
    bool tlsEnabled = false;

    static void validatePort(int port) {
        if (port < 1 || port > 65535) {
            throw InvalidConfigurationException(
                "Port must be between 1 and 65535, got: " + std::to_string(port));
        }
    }

    static void validateTimeout(int timeout) {
        if (timeout < 1 || timeout > 3600) {
            throw InvalidConfigurationException(
                "Timeout must be between 1 and 3600 seconds, got: " + std::to_string(timeout));
        }
    }

    static void validateMaxHeaderBytes(int bytes) {
        if (bytes < 1024 || bytes > 104857600) { // От 1KB до 100MB
            throw InvalidConfigurationException(
                "Max header size must be between 1KB and 100MB, got: " + std::to_string(bytes) + " bytes");
        }
    }

public:
    ServerConfig() = default;

    ServerConfig(int p, int readT, int writeT, bool log, int maxBytes, bool tls)
        : port(p), readTimeout(readT), writeTimeout(writeT),
        enableLogging(log), maxHeaderBytes(maxBytes), tlsEnabled(tls) {

        validatePort(port);
        validateTimeout(readTimeout);
        validateTimeout(writeTimeout);
        validateMaxHeaderBytes(maxHeaderBytes);
    }

    int getPort() const { return port; }
    int getReadTimeout() const { return readTimeout; }
    int getWriteTimeout() const { return writeTimeout; }
    bool isLoggingEnabled() const { return enableLogging; }
    int getMaxHeaderBytes() const { return maxHeaderBytes; }
    bool isTLSEnabled() const { return tlsEnabled; }

    void setPort(int p) {
        validatePort(p);
        port = p;
    }

    void setReadTimeout(int t) {
        validateTimeout(t);
        readTimeout = t;
    }

    void setWriteTimeout(int t) {
        validateTimeout(t);
        writeTimeout = t;
    }

    void setEnableLogging(bool enable) { enableLogging = enable; }

    void setMaxHeaderBytes(int bytes) {
        validateMaxHeaderBytes(bytes);
        maxHeaderBytes = bytes;
    }

    void setTLSEnabled(bool enable) { tlsEnabled = enable; }

    void display() const {
        std::cout << std::left << std::setw(25) << "Port:" << port << std::endl;
        std::cout << std::left << std::setw(25) << "Read Timeout:" << readTimeout << " seconds" << std::endl;
        std::cout << std::left << std::setw(25) << "Write Timeout:" << writeTimeout << " seconds" << std::endl;
        std::cout << std::left << std::setw(25) << "Logging:" << (enableLogging ? "Enabled" : "Disabled") << std::endl;
        std::cout << std::left << std::setw(25) << "Max Header Size:"
            << maxHeaderBytes << " bytes (" << (maxHeaderBytes / 1024.0 / 1024.0) << " MB)" << std::endl;
        std::cout << std::left << std::setw(25) << "TLS:" << (tlsEnabled ? "Enabled" : "Disabled") << std::endl;
    }

    std::string toString() const {
        return "Port=" + std::to_string(port) +
            ", ReadTimeout=" + std::to_string(readTimeout) + "s" +
            ", WriteTimeout=" + std::to_string(writeTimeout) + "s" +
            ", Logging=" + (enableLogging ? "Enabled" : "Disabled") +
            ", MaxHeaderBytes=" + std::to_string(maxHeaderBytes) +
            ", TLS=" + (tlsEnabled ? "Enabled" : "Disabled");
    }
};

#endif // SERVERCONFIG_H