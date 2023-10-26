/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:06:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 22:41:28 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

void	Server::kick(int const client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
		return ;
	}
	int	ch = _searchChannel(info.args[1]);
	if (ch == -1)
	{
		client->sendMessage(ERR_NOSUCHCHANNEL(client->getNick(), info.args[1]));
		return ;
	}
	Channel *channel = _channels[ch];
	if (!channel->isOperator(client_fd))
	{
		client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNick(), channel->getName()));
		return ;
	}
	if (!channel->isMember(info.args[2]))
	{
		client->sendMessage(ERR_USERNOTINCHANNEL(client->getNick(), info.args[2],\
		channel->getName()));
		return ;
	}
	if (!channel->isMember(client->getNick()))
	{
		client->sendMessage(ERR_NOTONCHANNEL(client->getNick(), channel->getName()));
		return ;
	}
	// int	user = _searchUser()
	// Client	*target = _channels[ch]
	std::string kickmsg = client->getNick() + "!" + client->getHostName() +\
	" KICK " + channel->getName() + " " + info.args[2] + " Kicked from channel";
	channel->sendMsg(NULL, kickmsg);
	channel->rmClient(*client);
}
