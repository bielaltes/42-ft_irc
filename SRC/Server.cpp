/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:19 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/17 23:21:46 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "../INC/Server.hpp"

Server::Server(int port, std::string psswd)
{
    _active = 1;
    _pollsfd = new pollfd[10];
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1) {
        perror("Binding failed");
    }

    if (listen(serverSocket, 5) == -1) {
        perror("Listening failed");
    }
    _serverfd.fd = serverSocket;
    _pollsfd[0].fd = serverSocket;
    _pollsfd[0].events = POLLIN;
}

Server::~Server()
{
    
}


void Server::LoopServer()
{
    while (42)
    {
        int poll_count = poll(this->_pollsfd, this->_active, -1);
		if (poll_count == -1)
		{
			perror("Poll error")
		}

		for (int i = 0; i < this->_active; i++)
		{
			if (this->_pollsfd[i].revents & POLLIN)
			{
				if (this->_pollsfd[i].fd == this->_serverfd)
					_NewClient();	
				else
					_Request(i);
			}
		}
    }
}

void Server::_NewClient()
{

}

void Server::_Request(int i)
{

}