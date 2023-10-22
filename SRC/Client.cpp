/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:45:25 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/22 10:20:49 by baltes-g         ###   ########.fr       */
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
    std::string sending = s + "\r\n"; 
    std::cout << "Sending message byytes: " << send(this->_fd, sending.c_str(), sending.size(), 0) << "to: "<< this->_fd<< std::endl;
}