#include "encrypted_transaction.h"
#include "encryption_utils.h"

EncryptedTransaction::EncryptedTransaction() {}

EncryptedTransaction::EncryptedTransaction(const std::vector<uint8_t>& encryptedData, const std::string& hash)
    : encryptedData(encryptedData), transactionHash(hash) {}

EncryptedTransaction::~EncryptedTransaction() {}

std::vector<uint8_t> EncryptedTransaction::getEncryptedData() const {
    return encryptedData;
}

std::string EncryptedTransaction::getHash() const {
    return transactionHash;
}

EncryptedTransaction EncryptedTransaction::encrypt(const Transaction& tx, const std::string& publicKey) {
    std::vector<uint8_t> serializedTx = tx.serialize();
    std::vector<uint8_t> encryptedData = EncryptionUtils::encrypt(serializedTx, publicKey);
    return EncryptedTransaction(encryptedData, tx.getHash());
}

Transaction EncryptedTransaction::decrypt(const std::string& privateKey) const {
    std::vector<uint8_t> decryptedData = EncryptionUtils::decrypt(encryptedData, privateKey);
    return Transaction::deserialize(decryptedData);
}
