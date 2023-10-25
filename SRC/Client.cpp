/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:45:25 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/25 17:09:14 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Client.hpp"

Client::Client(int fd) : _pswd(false)
{
    _fd = fd;
    _username = "";
    _realname = "";
    _nick = "";
    _buffer ="";
}

Client::~Client()
{
}

bool Client::operator=(const Client & cl)
{
    if (cl.getNick() == this->_nick)
        return true;
    return false;
}

void Client::sendMessage(const std::string &s) const
{
    std::string message = s + "\r\n";
    send(this->_fd, message.c_str(), message.size(), 0);
    
}