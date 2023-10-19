/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:26:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 18:53:18 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Channel.hpp"

Channel::Channel(const std::string &name, const Client &c)
{
    this->_name = name;
    _i = _t = _k = _o = _l = false;
    this->topic = std::string();
    this->_members = std::map<int,const Client*>();
    this->_invited = std::unordered_set<std::string>();
    this->_operators = std::unordered_set<std::string>();
    this->addClient(c);
    this->_operators.insert(c.getNick());
}

Channel::~Channel()
{

}


void Channel::addClient(const Client &c)
{
    std::pair<std::map<int, const Client*>::const_iterator, bool> it = _members.insert(std::make_pair(c.getFd(), &c));
}

void Channel::rmClient(const Client &c)
{
    _members.erase(c.getFd());
    _operators.erase(c.getNick());
}

void Channel::sendMsg(const Client &c, const std::string &msg) const
{
    std::map<int, const Client*>::const_iterator it = _members.begin();
    while (it != _members.end())
    {
        if ((*it).second->getNick() != c.getNick())
            (*it).second->SendMessage(msg);
    }
}

bool Channel::isMember(const std::string &nick)
{
    std::map<int,const Client*>::const_iterator it = _members.begin();
    while (it != _members.end())
    {
        if ((*it).second->getNick() == nick)
            return true;
    }
    return false;
}

void Channel::invite(const Client &c)
{
    _invited.insert(c.getNick());
}

