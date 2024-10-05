#include "key_management.h"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

KeyManagement::KeyManagement()
    : publicKeyPath("keys/public_key.pem"), privateKeyPath("keys/private_key.pem") {
    fs::create_directories(fs::path(publicKeyPath).parent_path());
}

KeyManagement::~KeyManagement() {}

void KeyManagement::generateKeyPair(std::string& publicKey, std::string& privateKey) {
    RSA* rsa = RSA_new();
    BIGNUM* e = BN_new();
    BN_set_word(e, RSA_F4);

    RSA_generate_key_ex(rsa, 2048, e, nullptr);

    BIO* pubBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSA_PUBKEY(pubBio, rsa);

    BIO* privBio = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(privBio, rsa, nullptr, nullptr, 0, nullptr, nullptr);

    size_t pubLen = BIO_pending(pubBio);
    publicKey.resize(pubLen);
    BIO_read(pubBio, publicKey.data(), pubLen);

    size_t privLen = BIO_pending(privBio);
    privateKey.resize(privLen);
    BIO_read(privBio, privateKey.data(), privLen);

    BIO_free_all(pubBio);
    BIO_free_all(privBio);
    RSA_free(rsa);
    BN_free(e);
}

bool KeyManagement::loadKeys(std::string& publicKey, std::string& privateKey) {
    std::ifstream pubFile(publicKeyPath, std::ios::binary);
    std::ifstream privFile(privateKeyPath, std::ios::binary);
    if (!pubFile.is_open() || !privFile.is_open()) {
        return false;
    }

    publicKey.assign((std::istreambuf_iterator<char>(pubFile)), std::istreambuf_iterator<char>());
    privateKey.assign((std::istreambuf_iterator<char>(privFile)), std::istreambuf_iterator<char>());

    pubFile.close();
    privFile.close();
    return true;
}

bool KeyManagement::storeKeys(const std::string& publicKey, const std::string& privateKey) {
    std::ofstream pubFile(publicKeyPath, std::ios::binary);
    std::ofstream privFile(privateKeyPath, std::ios::binary);
    if (!pubFile.is_open() || !privFile.is_open()) {
        return false;
    }

    pubFile << publicKey;
    privFile << privateKey;

    pubFile.close();
    privFile.close();
    return true;
}

bool KeyManagement::rotateKeys() {
    std::string newPublicKey, newPrivateKey;
    generateKeyPair(newPublicKey, newPrivateKey);
    return storeKeys(newPublicKey, newPrivateKey);
}
