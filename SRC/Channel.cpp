/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:26:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/11/02 09:13:17 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Channel.hpp"

Channel::Channel(Server *s, const std::string &name, const Client &c)
{
    _s = s;
    this->_name = name;
    _i = _t = _k = _o = _l = false;
    this->_topic = std::string();
    this->_members = std::set<int>();
    this->_invited = std::set<int>();
    this->_operators = std::set<int>();
    this->addClient(c);
    this->_operators.insert(c.getFd());
}

Channel::~Channel()
{
}

void Channel::addClient(const Client &c)
{
    _members.insert(c.getFd());
}

void    Channel::addOperator(const Client &c)
{
    _operators.insert(c.getFd());
}

void Channel::rmOperator(const Client &c)
{
    _operators.erase(c.getFd());
}

void Channel::rmClient(const Client &c)
{
    _members.erase(c.getFd());
    _operators.erase(c.getFd());
}

void Channel::sendMsg(const Client &c, const std::string &msg) const
{
    Client *aux;
    for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        aux = _s->getClient(*it);
        if (c.getNick() != aux->getNick())
            aux->sendMessage(msg);
    }
}

bool Channel::isMember(const std::string &nick)
{
    std::set<int>::const_iterator it = _members.begin();
    Client *aux;
    while (it != _members.end())
    {
        aux = _s->getClient(*it);
        if (aux->getNick() == nick)
            return true;
        ++it;
    }
    return false;
}

void Channel::invite(const Client &c)
{
    _invited.insert(c.getFd());
}

bool    Channel::isInvited(const int client_fd) const
{
    return _invited.count(client_fd) > 0;
}

bool    Channel::isOperator(const int client_fd) const
{
    return _operators.count(client_fd) > 0;
}

std::string Channel::getModes()
{
    std::string modes = "+";

    if (_i)
        modes.append("i");
    if (_t)
        modes.append("t");
    if (_k)
        modes.append("k");
    if (_o)
        modes.append("o");
    if (_l)
        modes.append("l");
    return modes;
}

std::string Channel::getModeArguments()
{
    std::string arguments = "";

    if (_k && !_l)
        arguments.append(_pass);
    if (_l && !_k)
        arguments.append(to_string(_limit));
    if (_k && _l)
        arguments.append(_pass + " " + to_string(_limit));
    return arguments;   
}
