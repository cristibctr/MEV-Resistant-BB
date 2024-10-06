#ifndef TRANSACTION_POOL_MANAGER_H
#define TRANSACTION_POOL_MANAGER_H

#include <mutex>
#include <vector>
#include "transaction_queue.h"
#include "encrypted_transaction.h"

class TransactionPoolManager {
public:
    TransactionPoolManager();
    ~TransactionPoolManager();

    void addTransaction(const EncryptedTransaction& encryptedTx);

    std::vector<EncryptedTransaction> getTransactionBatch(size_t batchSize);

    void removeTransaction(const std::string& transactionHash);

    size_t getPoolSize() const;

private:
    TransactionQueue transactionQueue;
    mutable std::mutex poolMutex;
};

#endif // TRANSACTION_POOL_MANAGER_H
