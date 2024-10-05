#ifndef ENCRYPTED_TRANSACTION_H
#define ENCRYPTED_TRANSACTION_H

#include <string>
#include <vector>
#include "transaction.h"

class EncryptedTransaction {
public:
    EncryptedTransaction();
    EncryptedTransaction(const std::vector<uint8_t>& encryptedData, const std::string& hash);
    ~EncryptedTransaction();

    std::vector<uint8_t> getEncryptedData() const;
    std::string getHash() const;

    static EncryptedTransaction encrypt(const Transaction& tx, const std::string& publicKey);
    Transaction decrypt(const std::string& privateKey) const;

private:
    std::vector<uint8_t> encryptedData;
    std::string transactionHash;
};

#endif // ENCRYPTED_TRANSACTION_H
