/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:08:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/27 07:16:03 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

cmd	Server::getPwds(cmd info)
{
	cmd pwds;
	if (info.args.size() > 2)
	{
		pwds = _parse(info.args[2], ',');
		return pwds;
	}
	return pwds;
}

int	Server::joinSingle(int const client_fd, cmd info, std::string target, int pwdNum)
{
	Client		*client = _clients[client_fd]; 

	if (target[0] != '&' && target[0] != '#')
	{
		client->sendMessage(ERR_BADCHANMASK(client->getNick()));
		return 0;
	}
	int ch = _searchChannel(target);
	if (ch != -1)
	{
		Channel		*channel = _channels[ch];
		cmd pwds = getPwds(info);
		if (channel->getK() && ((int)pwds.args.size() <= pwdNum || pwds.args[pwdNum] != channel->getPass()))
		{
			client->sendMessage(ERR_BADCHANNELKEY(client->getNick(), target));
			return 0;
		}
		if (channel->getI() && !channel->isInvited(client_fd))
		{
			client->sendMessage(ERR_INVITEONLYCHAN(client->getNick(), channel->getName()));
			return 0;
		}
		if (channel->getL() && channel->getLimit() > channel->getUsersNumber())
		{
			client->sendMessage(ERR_CHANNELISFULL(client->getNick(), channel->getName()));
			return 0;
		}
	}
	_addClientToChannel(client_fd, target);
	ch = _searchChannel(target);
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
	if (channel->getK())
		return 1;
	return 0;
}

void	Server::join(int const client_fd, cmd info)
{	
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 2)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(_clients[client_fd]->getNick(), info.args[0]));
		return ;
	}
	size_t found = info.args[1].find(',');
	if (found != std::string::npos)
	{
		int pwdNum = 0;
		cmd targets = _parse(info.args[1], ',');
		for (unsigned long i = 0; i < targets.args.size(); i++)
		{	
			pwdNum += joinSingle(client_fd, info, targets.args[i], pwdNum);
		}
	}
	else
		joinSingle(client_fd, info, info.args[1], info.args[2].length());

}

		// size_t found = info.args[1].find(',');
		// if (found != std::string::npos)
		// {
		// 	cmd targets = _parse(info.args[1], ',');
		// 	for (unsigned long i = 0; i < targets.args.size(); i++)
		// 	{		
		// 		if (targets.args[i][0] == '#' || targets.args[i][0] == '&')
		// 			privmsgChannel(client_fd, info, targets.args[i]);
		// 		else
		// 			privmsgUsers(client_fd, info, targets.args[i]);
		// 	}
		// }
