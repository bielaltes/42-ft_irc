/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:45:25 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/25 14:22:46 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Client.hpp"

Client::Client(int fd) : _pswd(false)
{
    _fd = fd;
    // _pswd = false;
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
    std::cout << "Sending message byytes: " \
    << send(this->_fd, message.c_str(), message.size(), 0) \
    << "to: "<< this->_fd << std::endl;
}