/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:08:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 17:49:51 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::join(int const client_fd, cmd info)
{	
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 2)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(_clients[client_fd]->getNick(), info.args[0]));
		return ;
	}
	if (info.args[1][0] != '&' && info.args[1][0] != '#')
	{
		client->sendMessage(ERR_BADCHANMASK(client->getNick()));
		return;
	}
	int ch = _searchChannel(info.args[1]);
	if (ch != -1)
	{
		Channel		*channel = _channels[ch];

		if (channel->getK() && info.args[2] != channel->getPass())
		{
			client->sendMessage(ERR_BADCHANNELKEY(client->getNick(), info.args[1]));
			return ;
		}
		if (channel->getI() && !channel->isInvited(client_fd))
		{
			client->sendMessage(ERR_INVITEONLYCHAN(client->getNick(), channel->getName()));
			return ;
		}
		if (channel->getL() && channel->getLimit() > channel->getUsersNumber())
		{
			client->sendMessage(ERR_CHANNELISFULL(client->getNick(), channel->getName()));
			return ;
		}
	}
	_addClientToChannel(client_fd, info.args[1]);
	ch = _searchChannel(info.args[1]);
	Channel *channel = _channels[ch];
	if (channel->getTopic() != "")
	{	
		client->sendMessage(RPL_TOPIC(client->getNick(), channel->getName(), channel->getTopic()));
		client->sendMessage(RPL_TOPICWHOTIME(client->getNick(), channel->getName(), channel->getTopic(), currentTime()));
	}
	else
		client->sendMessage(RPL_NOTOPIC(client->getNick(), channel->getName()));
	std::string	joinmsg = client->getNick() + "!" + client->getHostName() + " JOIN " + channel->getName();
	channel->sendMsg(NULL, joinmsg);
	names(client_fd, info);
}
