// TCP Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    // WSA debugging
    WSADATA wsaData = { 0 };
    int wsaResult = 0;
    
    // create socket
    int addressFamily = AF_INET; // cf_locale may not exist or work
    int socketType = SOCK_STREAM;
    int protocol = IPPROTO_TCP; // protocol paramater specific to addressFamily and socket specified; if 0 then service provider will choose protocol
    
    SOCKET listenSocket;
    sockaddr_in service;
    
    BOOL bOptVal = FALSE;
    int bOptLen = sizeof(BOOL);

    int iOptVal = 0;
    int intOptLen = sizeof(int);

    wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != NO_ERROR) {
        printf("WSAStartup failed: %d\n", wsaResult);
        return 1;
    }

    listenSocket = socket(addressFamily, socketType, protocol);
    if (listenSocket == INVALID_SOCKET) {
        printf("Socket function has failed with error = %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }
    // bind socket to localhost
    hostent* thisHost;
    char* ip;
    u_short port;
    port = 2700;
    thisHost = gethostbyname("");
    ip = inet_ntoa(*(struct in_addr*)*thisHost->h_addr_list);

    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr(ip);
    service.sin_port = htons(port);
    
    wsaResult = bind(listenSocket, (SOCKADDR*) &service, sizeof(service));
    if (wsaResult == SOCKET_ERROR) {
        printf("bind failed with error = %d\n", WSAGetLastError());
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    // Setsockopt or set socket options
    bOptVal = TRUE;
    wsaResult = setsockopt(listenSocket, SOL_SOCKET, SO_KEEPALIVE, (char *) &bOptVal, bOptLen);
    // listen for client connection 

    // accept connection; establish connection between server and client

    // client connect loop?

    // clean up socket connections
    closesocket(listenSocket);
    WSACleanup();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
