#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>

class Transaction {
public:
    Transaction();
    Transaction(const std::string& sender, const std::string& receiver, double amount, const std::string& metadata);
    ~Transaction();

    std::string getSender() const;
    std::string getReceiver() const;
    double getAmount() const;
    std::string getMetadata() const;
    std::string getHash() const;

    std::vector<uint8_t> serialize() const;
    static Transaction deserialize(const std::vector<uint8_t>& data);

    bool isValid() const;

private:
    std::string sender;
    std::string receiver;
    double amount;
    std::string metadata;
    std::string hash;

    void computeHash();
};

#endif // TRANSACTION_H
