#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Link Winsock library

#define PORT 8080
#define BUFFER_SIZE 1024

// Function to calculate monthly loan payment
double calculateLoanPayment(double principal, double rate, int term) {
    double monthlyRate = rate / 12 / 100;
    double payment = principal * monthlyRate / (1 - pow(1 + monthlyRate, -term));
    return payment;
}

void runTCPServer() {
    WSADATA wsaData;
    SOCKET server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed" << std::endl;
        return;
    }

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        std::cerr << "Socket creation error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return;
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) == SOCKET_ERROR) {
        std::cerr << "Setsockopt failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    // Listen for connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    std::cout << "TCP Server listening on port " << PORT << std::endl;

    // Accept client connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return;
    }

    // Read client data
    int valread = recv(new_socket, buffer, BUFFER_SIZE, 0);
    buffer[valread] = '\0';

    double principal, rate;
    int term;
    sscanf(buffer, "%lf %lf %d", &principal, &rate, &term);

    // Calculate loan payment
    double payment = calculateLoanPayment(principal, rate, term);

    // Send result back to client
    char result[BUFFER_SIZE];
    snprintf(result, BUFFER_SIZE, "Monthly Payment: $%.2f", payment);
    send(new_socket, result, strlen(result), 0);

    std::cout << "TCP Server: Result sent to client." << std::endl;

    closesocket(new_socket);
    closesocket(server_fd);
    WSACleanup();
}

int main() {
    runTCPServer();
    return 0;
}