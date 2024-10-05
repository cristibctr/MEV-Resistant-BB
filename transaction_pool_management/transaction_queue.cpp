#include "transaction_queue.h"

TransactionQueue::TransactionQueue() {}

TransactionQueue::~TransactionQueue() {}

void TransactionQueue::enqueue(const EncryptedTransaction& encryptedTx) {
    const std::string& hash = encryptedTx.getHash();
    if (transactionSet.find(hash) == transactionSet.end()) {
        queue.push(encryptedTx);
        transactionSet.insert(hash);
    }
}

std::vector<EncryptedTransaction> TransactionQueue::dequeueBatch(size_t batchSize) {
    std::vector<EncryptedTransaction> batch;
    while (!queue.empty() && batch.size() < batchSize) {
        EncryptedTransaction tx = queue.front();
        queue.pop();
        transactionSet.erase(tx.getHash());
        batch.push_back(tx);
    }
    return batch;
}

void TransactionQueue::remove(const std::string& transactionHash) {
    //TODO
}

size_t TransactionQueue::size() const {
    return queue.size();
}
