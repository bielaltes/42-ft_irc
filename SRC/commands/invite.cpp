/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:58:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/11/01 20:15:49 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::_invite(int client_fd, cmd &info)
{
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
		return ;
	}
	std::string	channel_name = info.args[2];
	std::string	invited_client = info.args[1];
	std::string s_client_fd = to_string(client_fd);

	int ch_num = _searchChannel(channel_name);
	if (ch_num == -1)
	{
		client->sendMessage(ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
		return ;
	}
	Channel	*channel = _channels[ch_num];
	if (!channel->isMember(client->getNick()))
	{
		client->sendMessage(ERR_NOTONCHANNEL(client->getNick(), channel_name));
		return ;
	}
	if (channel->isMember(invited_client))
	{
		client->sendMessage(ERR_USERONCHANNEL(client->getNick(), invited_client, channel_name));
		return ;
	}
	if (channel->getI() && !channel->isOperator(client_fd))
	{
		client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNick(), channel_name));
		return ;
	}
	int target_fd = _searchUser(invited_client);
	if (target_fd != -1)
	{
		Client	*target = _clients[target_fd];
		channel->invite(*target);
		target->sendMessage(":" + client->getNick() + " INVITE " + target->getNick() + " " + channel_name);
		client->sendMessage(RPL_INVITING(client->getNick(), target->getNick(), channel_name));
	}
	return ;
}
