/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:13:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/11/02 09:14:07 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

void	Server::_topic(int const client_fd, cmd &info)
{
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 2)
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
	if (!channel->isMember(client->getNick()))
	{
		client->sendMessage(ERR_NOTONCHANNEL(client->getNick(), channel->getName()));
		return ;
	}
	if (info.args.size() > 2 && channel->getT() && !channel->isOperator(client_fd))
	{
		client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNick(), channel->getName()));
		return ;
	}
	if (info.args.size() > 2 && info.args[2] == ":")
	{
		channel->setTopic("");
		std::string topicmsg = "TOPIC " + channel->getName() + " :" + channel->getTopic();
		channel->sendMsg(NULL, topicmsg);
		return ;
	}
	if (info.args.size() > 2)
	{
		std::string message = info.args[2];
		for (unsigned long i = 3; i < info.args.size(); i++)
			message.append(" " + info.args[i]);
		channel->setTopic(message);
		channel->sendMsg(NULL, RPL_TOPIC(client->getNick(), channel->getName(), channel->getTopic()));
		channel->sendMsg(NULL, RPL_TOPICWHOTIME(client->getNick(), channel->getName(), channel->getTopic(), _currentTime()));
	}
	else
	{
		if (channel->getTopic() != "")
		{
			client->sendMessage(RPL_TOPIC(client->getNick(), channel->getName(), channel->getTopic()));
			client->sendMessage(RPL_TOPICWHOTIME(client->getNick(), channel->getName(), channel->getTopic(), _currentTime()));
		}
		else
			client->sendMessage(RPL_NOTOPIC(client->getNick(), channel->getName()));
	}
}
