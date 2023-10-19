/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 22:45:25 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 13:50:10 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Client.hpp"

Client::Client()
{

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