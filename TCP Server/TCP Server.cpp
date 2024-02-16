// TCP Server.cpp : This file contains the 'main' function. Program execution begins and ends there.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <Winsock2.h>
#include <io.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
    /*** WINDOWS SOCKET WSA INIT NEEDED ***/
    WORD wVersionRequested;
    WSADATA wsaData; 
    int err;
    
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }
    /*** END ***/

    FILE* html_data;
    errno_t errn = fopen_s(&html_data, "C:\\Users\\alla0\\Documents\\GitHub\\TCP-Server\\TCP Server\\index.html", "r");
    if (html_data == NULL) {
        printf("Cannot open file no: %d\n", errn);
    }
    char buffer[128] = {0};
    char response_data[2048] = {0};

    while (fgets(buffer, sizeof(buffer), html_data)) {
        strcat_s(response_data, buffer);
    }
    char http_header[101] = { 0 }; // modern browsers dont handle headers well! must create a function that sets the size of this to the file size;
    strcat_s(http_header, "HTTP/1.1 200 OK\r\n\n"); // add this to the index.html then calculate size of html file
    strcat_s(http_header, response_data);
    
    // create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address = { 0 };
    address.sin_family = AF_INET;
    address.sin_port = htons(6969);
    address.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketfd, (struct sockaddr*)&address, sizeof(address))) {
        printf("NOT BINDED: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Bind to port 6969\n");

    if (listen(socketfd, 5)) {
        printf("NOT LISTENING: %d\n", WSAGetLastError());
        return 1;
    }
    printf("Listening to port 6969\n");
    int clientfd;
    while (1) {
        char client_msg[4096] = "";
        
        clientfd = accept(socketfd, NULL, NULL);
        
        /*
        _read(clientfd, client_msg, 4095);
        printf("%s\n", client_msg);

        
        char* method = NULL;
        char* route = NULL;
        char* client_http_header;
        strtok_s(client_msg, "\n", &client_http_header);
        printf("%s\n\n", client_http_header);

        char* header_token;
        strtok_s(client_http_header, " ", &header_token);

        int header_parse_counter = 0;

        while (header_token != NULL) {
            switch (header_parse_counter) {
            case 0:
                method = header_token;
            case 1:
                route = header_token;
            }
        }

        printf("The method is: %s\n", method);
        printf("The route is: %s\n", route);
        */
        // check if file descriptor is valid; if not then stop trying to use it
        
        send(clientfd, http_header, sizeof(http_header), 0);
        //_close(clientfd);
    }
    fclose(html_data);

    return 0;
}
