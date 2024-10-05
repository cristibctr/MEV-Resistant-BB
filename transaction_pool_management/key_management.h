#ifndef KEY_MANAGEMENT_H
#define KEY_MANAGEMENT_H

#include <string>

class KeyManagement {
public:
    KeyManagement();
    ~KeyManagement();

    void generateKeyPair(std::string& publicKey, std::string& privateKey);

    bool loadKeys(std::string& publicKey, std::string& privateKey);

    bool storeKeys(const std::string& publicKey, const std::string& privateKey);

    bool rotateKeys();

private:
    std::string publicKeyPath;
    std::string privateKeyPath;
};

#endif // KEY_MANAGEMENT_H
