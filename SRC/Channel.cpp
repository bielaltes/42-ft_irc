/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:26:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/25 03:40:21 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Channel.hpp"

Channel::Channel(Server *s, const std::string &name, const Client &c)
{
    _s = s;
    this->_name = name;
    _i = _t = _k = _o = _l = false;
    this->_topic = std::string();
    this->_members = std::unordered_set<int>();
    this->_invited = std::unordered_set<int>();
    this->_operators = std::unordered_set<int>();
    this->addClient(c);
    this->_operators.insert(c.getFd());
}

Channel::~Channel()
{

}


void Channel::addClient(const Client &c)
{
    _members.insert(c.getFd());
    Client *aux = _s->getClient(c.getFd());
    std::cout << "Added client: " << aux->getNick() << " with fd: " << aux->getFd() << " to channel " << this->getName() << std::endl;
}

void Channel::rmClient(const Client &c)
{
    _members.erase(c.getFd());
    _operators.erase(c.getFd());
}

void Channel::sendMsg(const Client &c, const std::string &msg) const
{
    std::cout << "Channel name "<< this->_name<<" Members size: " << _members.size() << std::endl;
    Client *aux;
    for (std::unordered_set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        aux = _s->getClient(*it);
        std::cout << "El nick es: " << aux->getNick() << std::endl;
        if (c.getNick() != aux->getNick())
            aux->sendMessage(msg);
    }
}

bool Channel::isMember(const std::string &nick)
{
    std::unordered_set<int>::const_iterator it = _members.begin();
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

void Channel::sendNames(const Client &c) const
{
    Client  *aux;
    for (std::unordered_set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        aux = _s->getClient(*it);
        std::string prefix = "";
        if (isOperator(aux->getFd()))
            prefix = "@";
        sendMsg(NULL, RPL_NAMREPLY(c.getNick(), _name, prefix, aux->getNick()));
    }
   for (std::unordered_set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        aux = _s->getClient(*it);
        aux->sendMessage(RPL_ENDOFNAMES(aux->getNick(), _name));
    }
}


