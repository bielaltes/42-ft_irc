/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:53:19 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/25 16:34:08 by baltes-g         ###   ########.fr       */
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
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        delete (*it).second;
    }
    for (size_t i = 0; i < _channels.size(); ++i)
        delete _channels[i];
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
                {
					_request(i);
                }
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
        std::cout << "bytes == 0" << std::endl;
        _rmClient(*_clients[this->_pollsfd[i].fd]);
        return;
    }
    std::cout << buffer << std::endl;

    std::string request(buffer, bytesRead);

    request = _clients[this->_pollsfd[i].fd]->getBuffer() + request;
    std::vector<std::string> aux = _splitByDelimiters(request, "\r\n");
    for (size_t j = 0; j < aux.size()-1; ++j)
        _runCmd(_parse(aux[j].c_str(), ' '), this->_pollsfd[i].fd);
    if (request.size() >= 2 && request.substr(request.size()-2, request.size()) == "\r\n")
    {
        _runCmd(_parse(aux[aux.size()-1].c_str(), ' '), this->_pollsfd[i].fd);
        _clients[this->_pollsfd[i].fd]->setBuffer("");
    }
    else
        _clients[this->_pollsfd[i].fd]->setBuffer(aux[aux.size() -1]);
    //std::string s = "Hello, you are fd: " + std::to_string(this->_pollsfd[i].fd) + "\n";
    //send(this->_pollsfd[i].fd, s.c_str(), s.size(), 0);
}

Client *Server::getClient(int fd)
{
    return _clients[fd];
}

bool Server::_existsClientNick(const std::string &nick)
{
    std::map<int, Client*>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if ((*it).second->getNick() == nick)
            return true;
        ++it;
    }
    return false;
}

bool Server::_existsClientUser(const std::string &user)
{
    std::map<int, Client*>::iterator it = _clients.begin();
    while (it != _clients.end())
    {
        if ((*it).second->getName() == user)
            return true;
        ++it;
    }
    return false;
}

void Server::_addClientToChannel(int fd, const std::string &ch_name)
{
    Client *c = _clients[fd];
    for (size_t i = 0; i < _channels.size(); ++i)
    {
        if (ch_name == _channels[i]->getName())
        {
            std::cout << "Afegint client"<< c->getNick() <<" a canal " << _channels[i]->getName()  << std::endl;
            _channels[i]->addClient(*c);
            return;
        }
    }
    _channels.push_back(new Channel(this, ch_name, *c));
    std::cout << "Afegint client" << c->getNick() << " al nou canal " << _channels[_channels.size()-1]->getName() << std::endl;
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

int Server::_searchUser(const std::string &name) //added by jareste
{
    std::cout << name << _clients.size() << std::endl;
    for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
        Client* client = it->second;
        if (client->getNick() == name)
           return it->first;
    }
    return -1;
}

cmd Server::_parse(std::string str, char c)
{
    cmd command;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, c)) {
        command.args.push_back(token);
    }
    return command;
}

void Server::_rmClient(const Client &c)
{
    for (size_t i = 0; i < _channels.size(); ++i)
        _channels[i]->rmClient(c);
    _clients.erase(c.getFd());
    close(c.getFd());
    for (size_t i = 0; i < _pollsfd.size(); ++i)
    {
        if (c.getFd() == _pollsfd[i].fd)
        {
            _pollsfd.erase(_pollsfd.begin() + i);
            --_active;
            break;
        }
    }
}


