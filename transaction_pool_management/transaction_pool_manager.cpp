#include "transaction_pool_manager.h"

TransactionPoolManager::TransactionPoolManager() {}

TransactionPoolManager::~TransactionPoolManager() {}

void TransactionPoolManager::addTransaction(const EncryptedTransaction& encryptedTx) {
    std::lock_guard<std::mutex> lock(poolMutex);
    transactionQueue.enqueue(encryptedTx);
}

std::vector<EncryptedTransaction> TransactionPoolManager::getTransactionBatch(size_t batchSize) {
    std::lock_guard<std::mutex> lock(poolMutex);
    return transactionQueue.dequeueBatch(batchSize);
}

void TransactionPoolManager::removeTransaction(const std::string& transactionHash) {
    std::lock_guard<std::mutex> lock(poolMutex);
    transactionQueue.remove(transactionHash);
}

size_t TransactionPoolManager::getPoolSize() const {
    std::lock_guard<std::mutex> lock(poolMutex);
    return transactionQueue.size();
}
