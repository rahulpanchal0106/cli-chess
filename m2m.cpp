//LAN Multiplayer Mode

#include <iostream>
#include <winsock2.h>
#include <limits>
#pragma comment(lib, "ws2_32.lib")

#define PORT 9999
#define MAX_BUFFER_SIZE 1024

using namespace std;

void startServer(SOCKET &serverSocket, sockaddr_in &serverAddr, sockaddr_in &clientAddr) {
    listen(serverSocket, 1);
    std::cout << "waiting for opponent to join..." << std::endl;
    
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    if (clientSocket != INVALID_SOCKET) {
        std::cout << "opponent has joined the game!" << std::endl;

        char buffer[MAX_BUFFER_SIZE];
        char server_message[MAX_BUFFER_SIZE];
        int bytesReceived;
        
        while (true) {
            // Clear buffers
            memset(buffer, 0, MAX_BUFFER_SIZE);
            memset(server_message, 0, MAX_BUFFER_SIZE);
            
            // Receive message from client
            bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                buffer[bytesReceived] = '\0';
                std::cout << "opponent's move: " << buffer << std::endl;
                
                // Get server's response
                std::cout << "Your Move: ";
                std::cin.getline(server_message, sizeof(server_message));
                
                // Send response to client
                send(clientSocket, server_message, strlen(server_message), 0);
            } else {
                std::cout << "opponent disconnected." << std::endl;
                break;
            }
        }
        closesocket(clientSocket);
    }
}

void startClient(SOCKET &clientSocket, sockaddr_in &serverAddr) {
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed!" << std::endl;
        return;
    }

    std::cout << "Connected to opponent!" << std::endl;

    char buffer[MAX_BUFFER_SIZE];
    char message[MAX_BUFFER_SIZE];
    
    // Clear the input buffer once at the start
    std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (true) {
        // Clear buffers
        memset(buffer, 0, MAX_BUFFER_SIZE);
        memset(message, 0, MAX_BUFFER_SIZE);
        
        // Get message from user
        std::cout << "Your move: ";
        std::cin.getline(message, sizeof(message));
        
        if (strlen(message) == 0) {
            std::cout << "Exiting..." << std::endl;
            break;
        }

        // Send message to server
        send(clientSocket, message, strlen(message), 0);
        
        // Receive server's response
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            std::cout << "opponent's move: " << buffer << std::endl;
        } else {
            std::cout << "opponent disconnected." << std::endl;
            break;
        }
    }
}

int main() {
    WSADATA wsaData;
    SOCKET socketHandle;
    sockaddr_in addr;
    char buffer[MAX_BUFFER_SIZE];

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed!" << std::endl;
        return -1;
    }

    // Create socket
    socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketHandle == INVALID_SOCKET) {
        std::cerr << "Socket creation failed!" << std::endl;
        return -1;
    }

    // Setup the address (for both server and client roles)
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT); // Port number
    addr.sin_addr.s_addr = INADDR_ANY;  // Use any available IP for server or use a specific IP for client

    std::cout << "Choose your role: 1 for Hosting a Game, 2 for Joining a Game: ";
    int role;
    std::cin >> role;
    std::cin.ignore();  // Ignore the newline character left by std::cin after reading the role

    if (role == 1) {
        // Server Role
        if (bind(socketHandle, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed!" << std::endl;
            return -1;
        }
        std::cout << "Creating a Game Space for you two..." << std::endl;
        startServer(socketHandle, addr, addr);
    } else if (role == 2) {
        // Client Role
        std::cout << "Enter server IP address: ";
        std::string serverIp;
        std::cin >> serverIp;
        addr.sin_addr.s_addr = inet_addr(serverIp.c_str());  // Set server IP address

        startClient(socketHandle, addr);
    } else {
        std::cerr << "Invalid choice!" << std::endl;
    }

    // Cleanup
    closesocket(socketHandle);
    WSACleanup();
    return 0;
}
