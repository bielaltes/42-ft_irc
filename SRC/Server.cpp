/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:19 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 20:42:21 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Server.hpp"

Server::Server(int port,const std::string &psswd)
{
    _psswd = psswd;
    _port = port;
    _clients = std::map<int, Client*>();
    _channels = std::vector<Channel*>();
    
    _active = 1;
    _pollsfd = std::vector<pollfd>(1); 
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
        int poll_count = poll(this->_pollsfd.data(), this->_active, -1);
		if (poll_count == -1)
		{
			perror("Poll error");
		}

		for (int i = 0; i < this->_active; i++)
		{
			if (this->_pollsfd[i].revents & POLLIN)
			{
				if (this->_pollsfd[i].fd == this->_serverfd.fd)
					_newClient();	
				else
					_request(i);
			}
		}
    }
}

void Server::_newClient()
{
    struct sockaddr_storage	remotaddr;
	socklen_t				addrlen;
	int newfd;

	addrlen = sizeof remotaddr;
	newfd = accept(this->_serverfd.fd, (struct sockaddr*)&remotaddr, &addrlen);
	if (newfd == -1)
		std::cout << "accept() error: " << strerror(errno) << std::endl;
	else
	{
        struct pollfd p;
        this->_pollsfd.push_back(p);
        this->_pollsfd[this->_active].fd = newfd;
        this->_pollsfd[this->_active].events = POLLIN;
        this->_clients.insert(std::pair<int, Client *>(newfd, new Client(newfd)));
        this->_active++;
		// std::string s = "Welcome";
		//send(newfd, s.c_str(), s.length(), 0);
	}
}

void Server::_request(int i)
{
    char buffer[1024];
    ssize_t bytesRead = recv(this->_pollsfd[i].fd, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Recv failed");
        return;
    }

    if (bytesRead == 0) {
        // Client closed the connection
        return;
    }

    std::string request(buffer, bytesRead);

    _runCmd(_parse(request.c_str()), this->_pollsfd[i].fd);
    //std::string s = "Hello, you are fd: " + std::to_string(this->_pollsfd[i].fd) + "\n";
    //send(this->_pollsfd[i].fd, s.c_str(), s.size(), 0);
}

bool Server::_existsClient(const std::string &nick)
{
    std::map<int, Client*>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if ((*it).second->getNick() == nick)
            return true;
    }
    return false;
}

void Server::_addClientToChannel(int fd, const std::string &ch_name)
{
    Client c = *_clients[fd];
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        if (ch_name == _channels[i]->getName())
        {
            std::cout << "biel tontu que poses males condicions" << std::endl;
            _channels[i]->addClient(c);
            return;
        }
    }
    std::cout << _channels.size() << std::endl;
    _channels.push_back(new Channel(ch_name, c));
    std::cout << _channels.size() << std::endl;
}

int Server::_searchChannel(const std::string &name)
{
    std::cout << name << _channels.size() << std::endl;
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        std::cout << "ch: " << _channels[i]->getName() << " name: |"<< name+"|"<< std::endl;
        if (name.compare(_channels[i]->getName()) == 0)
            return i;
    }
    return -1;
}
