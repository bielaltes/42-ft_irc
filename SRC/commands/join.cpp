/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:08:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 03:24:58 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::join(int const client_fd, cmd info)
{	
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 2)// || (channel.getK() && info.args.size() < 3))
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

		if (channel->getK() && info.args[2] != channel->getPass())//nook
		{
			client->sendMessage(ERR_BADCHANNELKEY(client->getNick(), info.args[1]));
			return ;
		}
		if (channel->getI() && !channel->isInvited(client_fd))//nook
		{
			std::cout << channel->isInvited(client_fd) << std::endl;
			client->sendMessage(ERR_INVITEONLYCHAN(client->getNick(), channel->getName()));
			return ;
		}
		if (channel->getL() && channel->getLimit() > channel->getUsersNumber())//nook
		{
			client->sendMessage(ERR_CHANNELISFULL(client->getNick(), channel->getName()));
			return ;
		}
	}
	_addClientToChannel(client_fd, info.args[1]);
	ch = _searchChannel(info.args[1]);
	Channel *channel = _channels[ch];
	if (channel->getTopic() != "")//nook
	{	
		client->sendMessage(RPL_TOPIC(client->getNick(), channel->getName(), channel->getTopic())); //S'ENVIA AL CLIENT QUE ACABA D'ENTRAR
		client->sendMessage(RPL_TOPICWHOTIME(client->getNick(), channel->getName(), channel->getTopic(), "99/99/2024"));//S'ENVIA AL CLIENT TMB DESPUES DE L'ANTERIOR
	}
	else
		client->sendMessage(RPL_NOTOPIC(client->getNick(), channel->getName()));
	std::string	joinmsg = client->getNick() + "!" + client->getHostName() + " JOIN " + channel->getName();
	channel->sendMsg(NULL, joinmsg);
	names(client_fd, info);
}
