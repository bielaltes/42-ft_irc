/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:08:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 01:11:52 by jareste-         ###   ########.fr       */
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
// if (client is banned from chan)
// {
// 	ERR_BANNEDFROMCHAN(client, channel);
// 	return ;
// }
		if (channel->getI() && !channel->isInvited(client_fd))//nook
		{
			std::cout << channel->isInvited(client_fd) << std::endl;
			client->sendMessage(ERR_INVITEONLYCHAN(client->getNick(), channel->getName()));
			return ;
		}
		if (channel->getL() && channel->getLimit() > channel->getUserNumber())//nook
		{
			client->sendMessage(ERR_CHANNELISFULL(client->getNick(), channel->getName()));
			return ;
		}
	}
		_addClientToChannel(client_fd, info.args[1]);
		// int ch = _searchChannel(info.args[1]);
			// if (channel has topic)//nook
			// {	
			// 	client.SendMessage(RPL_TOPIC(client, channel, topic)) //S'ENVIA AL CLIENT QUE ACABA D'ENTRAR
			// 	client.SendMessage(RPL_TOPICWHOTIME(client, channel, topic, setat))s //S'ENVIA AL CLIENT TMB DESPUES DE L'ANTERIOR
			// }
			// else
		// client.SendMessage(RPL_NOTOPIC(client_fd, client, _channels));
	// _channels[ch]->sendMsg(client, info.args[2]);//haurem d'avisar a tots que algú s'ha unit
}
