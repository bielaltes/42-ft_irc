/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:06:33 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/13 23:28:27 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <poll.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <port> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    std::string password = argv[2];

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        perror("Binding failed");
        return 1;
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Listening failed");
        return 1;
    }

    struct pollfd pollfd;
    pollfd.fd = serverSocket;
    pollfd.events = POLLIN;

    while (true) {
        int pollResult = poll(&pollfd, 1, -1);
        if (pollResult == -1) {
            perror("Poll failed");
            break;
        }

        if (pollfd.revents & POLLIN) {
            int clientSocket = accept(serverSocket, nullptr, nullptr);
            if (clientSocket == -1) {
                perror("Accept failed");
                continue;
            }

            while (true)
            {
                char buffer[1024];
                ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesRead == -1) {
                    perror("Recv failed");
                    break;
                }

                if (bytesRead == 0) {
                    // Client closed the connection
                    break;
                }

                std::string request(buffer, bytesRead);
                if (request == password+'\n') {
                    std::cout << "Access granted!: |" << request.substr(0, request.length()-1) << '|' << std::endl;
                    
                } else if (request != password+'\n'){
                    std::cout << "Access f: " <<"|"<< password << "| |" << request.substr(0, request.length()-1) << '|' << std::endl;
                }
            }
        }
    }

    close(serverSocket);

    return 0;
}