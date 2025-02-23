#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Link Winsock library

#define PORT 8080
#define BUFFER_SIZE 1024

void runTCPClient() {
    WSADATA wsaData;
    SOCKET sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported" << std::endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return;
    }

    // Get user input
    double principal, rate;
    int term;
    std::cout << "Enter principal amount: ";
    std::cin >> principal;
    std::cout << "Enter annual interest rate (%): ";
    std::cin >> rate;
    std::cout << "Enter loan term (months): ";
    std::cin >> term;

    // Send data to server
    char request[BUFFER_SIZE];
    snprintf(request, BUFFER_SIZE, "%lf %lf %d", principal, rate, term);
    send(sock, request, strlen(request), 0);

    // Receive result from server
    int valread = recv(sock, buffer, BUFFER_SIZE, 0);
    buffer[valread] = '\0';
    std::cout << "Server response: " << buffer << std::endl;

    closesocket(sock);
    WSACleanup();
}

int main() {
    runTCPClient();
    return 0;
}