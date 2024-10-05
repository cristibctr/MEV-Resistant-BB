#include "config.h"
#include <fstream>
#include <json/json.h>

Config::Config()
    : maxPoolSize(10000),
    maxBatchSize(100),
    encryptionAlgorithm("RSA2048"),
    networkAddress("0.0.0.0"),
    networkPort(8080) {}

Config& Config::getInstance() {
    static Config instance;
    return instance;
}

bool Config::loadConfig(const std::string& filePath) {
    std::ifstream configFile(filePath);
    if (!configFile.is_open()) {
        return false;
    }

    Json::Value root;
    configFile >> root;

    maxPoolSize = root.get("maxPoolSize", 10000).asUInt();
    maxBatchSize = root.get("maxBatchSize", 100).asUInt();
    encryptionAlgorithm = root.get("encryptionAlgorithm", "RSA2048").asString();
    networkAddress = root.get("networkAddress", "0.0.0.0").asString();
    networkPort = root.get("networkPort", 8080).asInt();

    configFile.close();
    return true;
}
