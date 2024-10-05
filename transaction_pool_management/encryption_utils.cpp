#include "encryption_utils.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

std::vector<uint8_t> EncryptionUtils::encrypt(const std::vector<uint8_t>& data, const std::string& publicKey) {
    BIO* keyBio = BIO_new_mem_buf(publicKey.c_str(), -1);
    RSA* rsa = PEM_read_bio_RSA_PUBKEY(keyBio, nullptr, nullptr, nullptr);
    if (!rsa) {
        BIO_free(keyBio);
        return {};
    }

    std::vector<uint8_t> encryptedData(RSA_size(rsa));
    int result = RSA_public_encrypt(
        data.size(),
        data.data(),
        encryptedData.data(),
        rsa,
        RSA_PKCS1_OAEP_PADDING
    );

    RSA_free(rsa);
    BIO_free(keyBio);

    if (result == -1) {
        return {};
    }

    encryptedData.resize(result);
    return encryptedData;
}

std::vector<uint8_t> EncryptionUtils::decrypt(const std::vector<uint8_t>& encryptedData, const std::string& privateKey) {
    BIO* keyBio = BIO_new_mem_buf(privateKey.c_str(), -1);
    RSA* rsa = PEM_read_bio_RSAPrivateKey(keyBio, nullptr, nullptr, nullptr);
    if (!rsa) {
        BIO_free(keyBio);
        return {};
    }

    std::vector<uint8_t> decryptedData(RSA_size(rsa));
    int result = RSA_private_decrypt(
        encryptedData.size(),
        encryptedData.data(),
        decryptedData.data(),
        rsa,
        RSA_PKCS1_OAEP_PADDING
    );

    RSA_free(rsa);
    BIO_free(keyBio);

    if (result == -1) {
        return {};
    }

    decryptedData.resize(result);
    return decryptedData;
}

std::string EncryptionUtils::computeHash(const std::vector<uint8_t>& data) {
    unsigned char hashResult[SHA256_DIGEST_LENGTH];
    SHA256(data.data(), data.size(), hashResult);

    std::stringstream hexStream;
    for (unsigned char i : hashResult) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(i);
    }
    return hexStream.str();
}
