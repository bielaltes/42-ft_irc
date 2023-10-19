/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:45:25 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 16:16:00 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Client.hpp"

Client::Client(int fd) : _fd(fd)
{
    _pswd = false;
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

void Client::SendMessage(const std::string &s)
{
    send(this->_fd, s.c_str(), s.size(), 0);
}