#include "transaction.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

Transaction::Transaction() : amount(0.0) {}

Transaction::Transaction(const std::string& sender, const std::string& receiver, double amount, const std::string& metadata)
    : sender(sender), receiver(receiver), amount(amount), metadata(metadata) {
    computeHash();
}

Transaction::~Transaction() {}

std::string Transaction::getSender() const {
    return sender;
}

std::string Transaction::getReceiver() const {
    return receiver;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getMetadata() const {
    return metadata;
}

std::string Transaction::getHash() const {
    return hash;
}

void Transaction::computeHash() {
    std::stringstream ss;
    ss << sender << receiver << amount << metadata;
    std::string data = ss.str();

    unsigned char hashResult[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(data.c_str()), data.size(), hashResult);

    std::stringstream hexStream;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        hexStream << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(hashResult[i]);
    }
    hash = hexStream.str();
}

std::vector<uint8_t> Transaction::serialize() const {
    // Simple serialization: concatenate fields with delimiter
    std::string data = sender + "|" + receiver + "|" + std::to_string(amount) + "|" + metadata + "|" + hash;
    return std::vector<uint8_t>(data.begin(), data.end());
}

Transaction Transaction::deserialize(const std::vector<uint8_t>& data) {
    std::string dataStr(data.begin(), data.end());
    std::stringstream ss(dataStr);
    std::string item;
    std::vector<std::string> tokens;

    while (std::getline(ss, item, '|')) {
        tokens.push_back(item);
    }

    if (tokens.size() != 5) {
        return Transaction();
    }

    Transaction tx(tokens[0], tokens[1], std::stod(tokens[2]), tokens[3]);
    tx.hash = tokens[4];
    return tx;
}

bool Transaction::isValid() const {
    Transaction temp(sender, receiver, amount, metadata);
    return temp.getHash() == hash;
}
