#ifndef CONFIG_H
#define CONFIG_H

#include <string>

class Config {
public:
    static Config& getInstance();

    size_t maxPoolSize;
    size_t maxBatchSize;
    std::string encryptionAlgorithm;
    std::string networkAddress;
    int networkPort;

    bool loadConfig(const std::string& filePath);

private:
    Config();
    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;
};

#endif // CONFIG_H
