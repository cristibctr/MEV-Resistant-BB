#ifndef NETWORK_INTERFACE_H
#define NETWORK_INTERFACE_H

#include <string>
#include <functional>
#include "encrypted_transaction.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <unistd.h>
#endif

class NetworkInterface {
public:
    NetworkInterface();
    ~NetworkInterface();

    bool startListening(const std::string& address, int port);

    void stopListening();

    void setTransactionHandler(const std::function<void(const EncryptedTransaction&)>& handler);

private:
    int serverSocket;
    bool isListening;
    std::function<void(const EncryptedTransaction&)> transactionHandler;

    void acceptConnections();
};

#endif // NETWORK_INTERFACE_H
