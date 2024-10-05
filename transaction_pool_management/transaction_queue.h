#ifndef TRANSACTION_QUEUE_H
#define TRANSACTION_QUEUE_H

#include <queue>
#include <unordered_set>
#include "encrypted_transaction.h"

class TransactionQueue {
public:
    TransactionQueue();
    ~TransactionQueue();

    void enqueue(const EncryptedTransaction& encryptedTx);

    std::vector<EncryptedTransaction> dequeueBatch(size_t batchSize);

    void remove(const std::string& transactionHash);

    size_t size() const;

private:
    std::queue<EncryptedTransaction> queue;
    std::unordered_set<std::string> transactionSet;
};

#endif // TRANSACTION_QUEUE_H
