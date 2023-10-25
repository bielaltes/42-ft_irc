/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:13:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 02:38:09 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  //    Command: TOPIC
  // Parameters: <channel> [<topic>]
#include "../../INC/Server.hpp"

void	Server::topic(int const client_fd, cmd info)
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
	if (channel->getT() && !channel->isOperator(client_fd))
	{
		client->sendMessage(ERR_CHANOPRIVSNEEDED(client->getNick(), channel->getName()));
		return ;
	}
	if (info.args.size() == 2)
	{
		channel->setTopic("");
		return ;
	}
	std::string message = info.args[2];
	for (unsigned long i = 3; i < info.args.size(); i++)
		message.append(" " + info.args[i]);
	channel->setTopic(message);
	std::string topicmsg = "TOPIC " + channel->getName() + " :" + channel->getTopic();
	channel->sendMsg(NULL, topicmsg);
	//hem d'informar del topic al que estem fent set.
}

//aquests 3 s'han d'enviar al entrar a un canal,
// notopic si no hi ha, els altres dos si hi ha topic.
// RPL_NOTOPIC (331)
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)