#ifndef ENCRYPTION_UTILS_H
#define ENCRYPTION_UTILS_H

#include <string>
#include <vector>

class EncryptionUtils {
public:
    static std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data, const std::string& publicKey);

    static std::vector<uint8_t> decrypt(const std::vector<uint8_t>& encryptedData, const std::string& privateKey);

    static std::string computeHash(const std::vector<uint8_t>& data);

};

#endif // ENCRYPTION_UTILS_H
