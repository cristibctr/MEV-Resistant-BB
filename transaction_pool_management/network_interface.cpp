#include "network_interface.h"
#include <thread>
#include <vector>

#ifdef _WIN32
NetworkInterface::NetworkInterface() : serverSocket(INVALID_SOCKET), isListening(false) {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}

NetworkInterface::~NetworkInterface() {
    stopListening();
    WSACleanup();
}
#else
NetworkInterface::NetworkInterface() : serverSocket(-1), isListening(false) {}

NetworkInterface::~NetworkInterface() {
    stopListening();
}
#endif

bool NetworkInterface::startListening(const std::string& address, int port) {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket ==
#ifdef _WIN32
        INVALID_SOCKET
#else
        - 1
#endif
        ) {
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
#ifdef _WIN32
    InetPton(AF_INET, address.c_str(), &serverAddr.sin_addr);
#else
    inet_aton(address.c_str(), &serverAddr.sin_addr);
#endif

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) ==
#ifdef _WIN32
        SOCKET_ERROR
#else
        - 1
#endif
        ) {
#ifdef _WIN32
        closesocket(serverSocket);
#else
        close(serverSocket);
#endif
        return false;
    }

    if (listen(serverSocket, SOMAXCONN) ==
#ifdef _WIN32
        SOCKET_ERROR
#else
        - 1
#endif
        ) {
#ifdef _WIN32
        closesocket(serverSocket);
#else
        close(serverSocket);
#endif
        return false;
    }

    isListening = true;
    std::thread(&NetworkInterface::acceptConnections, this).detach();
    return true;
}

void NetworkInterface::stopListening() {
    isListening = false;
    if (serverSocket !=
#ifdef _WIN32
        INVALID_SOCKET
#else
        - 1
#endif
        ) {
#ifdef _WIN32
        closesocket(serverSocket);
#else
        close(serverSocket);
#endif
        serverSocket =
#ifdef _WIN32
            INVALID_SOCKET;
#else
            - 1;
#endif
    }
}

void NetworkInterface::setTransactionHandler(const std::function<void(const EncryptedTransaction&)>& handler) {
    transactionHandler = handler;
}

void NetworkInterface::acceptConnections() {
    while (isListening) {
#ifdef _WIN32
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
#else
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket == -1) {
#endif
            // Handle error
            continue;
        }

        std::thread([this, clientSocket]() {
            std::vector<uint8_t> buffer(4096);
#ifdef _WIN32
            int bytesRead = recv(clientSocket, reinterpret_cast<char*>(buffer.data()), buffer.size(), 0);
#else
            ssize_t bytesRead = read(clientSocket, buffer.data(), buffer.size());
#endif
            if (bytesRead > 0) {
                buffer.resize(bytesRead);
                EncryptedTransaction encryptedTx(buffer, ""); //TODO: Hash to be computed
                if (transactionHandler) {
                    transactionHandler(encryptedTx);
                }
            }
#ifdef _WIN32
            closesocket(clientSocket);
#else
            close(clientSocket);
#endif
            }).detach();
        }
    }
