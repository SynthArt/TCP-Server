// TCP Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <Winsock2.h>
#include <io.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address = {
        AF_INET,
        htons(9999),
        0
    };

    if (bind(socketfd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        printf("NOT BINDED\n");
    }

    listen(socketfd, 10);

    int clientfd = accept(socketfd, 0, 0);
    // stdin - 0
    struct pollfd fds[2] = {
        {    
            0,
            POLLIN,
            0
        },
        {
            clientfd,
            POLLIN,
            0
        }
    };
    for (;;) {
        char buffer[256] = { 0 };
        WSAPoll(fds, 2, 50000);
        if (fds[0].revents & POLLIN) {
            _read(0, buffer, 255);
            send(clientfd, buffer, 255, 0);
        }
        else if (fds[1].revents & POLLIN) {
            if (recv(clientfd, buffer, 255, 0) == 0) {
                return 0;
            }
            printf("%s\n",buffer);
        }
    }

    return 0;
}
