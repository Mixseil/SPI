#ifndef SERVERCONFIG_H
#define SERVERCONFIG_H

#include <iostream>
#include <string>
#include <iomanip>

class ServerConfig {
private:
    int port = 8080;
    int readTimeout = 15;
    int writeTimeout = 15;
    bool enableLogging = false;
    int maxHeaderBytes = 1048576; 
    bool tlsEnabled = false;

public:
    ServerConfig() = default;

    ServerConfig(int p, int readT, int writeT, bool log, int maxBytes, bool tls)
        : port(p), readTimeout(readT), writeTimeout(writeT),
        enableLogging(log), maxHeaderBytes(maxBytes), tlsEnabled(tls) {}

    int getPort() const { return port; }
    int getReadTimeout() const { return readTimeout; }
    int getWriteTimeout() const { return writeTimeout; }
    bool isLoggingEnabled() const { return enableLogging; }
    int getMaxHeaderBytes() const { return maxHeaderBytes; }
    bool isTLSEnabled() const { return tlsEnabled; }

    void setPort(int p) { port = p; }
    void setReadTimeout(int t) { readTimeout = t; }
    void setWriteTimeout(int t) { writeTimeout = t; }
    void setEnableLogging(bool enable) { enableLogging = enable; }
    void setMaxHeaderBytes(int bytes) { maxHeaderBytes = bytes; }
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