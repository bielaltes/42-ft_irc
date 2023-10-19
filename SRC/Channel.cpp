/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:26:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 16:00:30 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Channel.hpp"

Channel::Channel(const std::string &name)
{
    this->_name = name;
    _i = _t = _k = _o = _l = false;
    this->topic = std::string();
    this->_members = std::map<int, Client*>();
    this->_invited = std::unordered_set<std::string>();
    this->_operators = std::unordered_set<std::string>();
}

Channel::~Channel()
{

}


void Channel::AddClient(Client &c)
{
    std::pair<std::map<int, Client*>::iterator, bool> it = _members.insert(std::make_pair(c.getFd(), &c));
}

void Channel::RmClient(Client &c)
{
    _members.erase(c.getFd());
    _operators.erase(c.getNick());
}

void Channel::SendMsg(Client &c, const std::string &msg)
{
    std::map<int, Client*>::iterator it = _members.begin();
    while (it != _members.end())
    {
        if ((*it).second->getNick() != c.getNick())
            (*it).second->SendMessage(msg);
    }
}

bool Channel::isMember(std::string &nick)
{
    std::map<int, Client*>::iterator it = _members.begin();
    while (it != _members.end())
    {
        if ((*it).second->getNick() == nick)
            return true;
    }
    return false;
}


void Channel::invite(Client &c)
{
    _invited.insert(c.getNick());
}