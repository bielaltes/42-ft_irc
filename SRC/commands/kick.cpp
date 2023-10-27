/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:06:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/27 19:56:34 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

Client	*Server::kickSingle(int const client_fd, std::string target, Channel *channel)
{
	Client		*client = _clients[client_fd]; 
	
	if (!channel->isMember(target))
	{
		client->sendMessage(ERR_USERNOTINCHANNEL(client->getNick(), target,\
		channel->getName()));
		return NULL;
	}
	if (!channel->isMember(client->getNick()))
	{
		client->sendMessage(ERR_NOTONCHANNEL(client->getNick(), channel->getName()));
		return NULL;
	}
	int	user = _searchUser(target);
	if (user == -1 || user == client_fd)
		return NULL;
	Client	*cTarget = _clients[user];
	std::string kickmsg = ":" + client->getNick() + "!" + client->getHostName() +\
	" KICK " + channel->getName() + " " + cTarget->getName() + " Kicked from channel";
	channel->sendMsg(NULL, kickmsg);
	channel->rmClient(*cTarget);
	return cTarget;
}

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
	size_t found = info.args[2].find(',');
	if (found != std::string::npos)
	{
		unsigned long i;
		cmd targets = _parse(info.args[2], ',');
		for (i = 0; i < targets.args.size(); i++)
		{
			kickSingle(client_fd, targets.args[i], channel);
		}
	}
	else
		kickSingle(client_fd, info.args[2], channel);

}
