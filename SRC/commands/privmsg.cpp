/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:58:43 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/31 12:28:18 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::_privmsgChannel(int const client_fd, cmd &info, std::string &target_name)
{
	Client		*client = _clients[client_fd]; 

	if (_searchChannel(target_name) == -1)
	{
		client->sendMessage(ERR_NOSUCHNICK(client->getName(), client->getNick()));
		return ;
	}
	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NOTEXTTOSEND(client->getName()));
		return ;
	}
	int tst = _searchChannel(target_name);
	std::string	message = ":" + client->getNick() + " PRIVMSG " + _channels[tst]->getName();
	if (info.args[2][0] != ':')
		info.args[2] = ":" + info.args[2];
	for (unsigned long i = 2; i < info.args.size(); i++)
		message.append(" " + info.args[i]);
	_channels[tst]->sendMsg(*client, message);
	if (info.args[2] == ":hola" || info.args[2] == "hola")
	{
		std::string	botResponse = ":SegfaultBot PRIVMSG " + _channels[tst]->getName() + " Segmentation fault detected";
		client->sendMessage(botResponse);
	}
}

void	Server::_privmsgUsers(int const client_fd, cmd &info, std::string &target_name)
{
	Client		*client = _clients[client_fd]; 
	std::string	nickname = client->getNick();

	if (info.args.size() < 2 || target_name[0] == ':')
	{
		client->sendMessage(ERR_NORECIPIENT(client->getName(), "PRIVMSG"));
		return ;
	}
	if (!_existsClientNick(target_name))
	{
		client->sendMessage(ERR_NOSUCHNICK(client->getName(), target_name));
		return ;
	}
	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NOTEXTTOSEND(client->getName()));
		return ;
	}
	int target_fd = _searchUser(target_name);
	if (target_fd != -1)
	{
		Client	*target = _clients[target_fd];
		if (info.args[2][0] != ':')
			info.args[2] = ":" + info.args[2];
		std::string	message = ":" + client->getNick() + "!" +  client->getHostName() + " PRIVMSG " + target->getNick();
		for (unsigned long i = 2; i < info.args.size(); i++)
			message.append(" " + info.args[i]);
		target->sendMessage(message);
	}
}

void	Server::_privmsg(int const client_fd, cmd &info)
{
	if (info.args.size() > 1)
	{
		size_t found = info.args[1].find(',');
		if (found != std::string::npos)
		{
			cmd targets = _parse(info.args[1], ',');
			for (unsigned long i = 0; i < targets.args.size(); i++)
			{		
				if (targets.args[i][0] == '#' || targets.args[i][0] == '&')
					_privmsgChannel(client_fd, info, targets.args[i]);
				else
					_privmsgUsers(client_fd, info, targets.args[i]);
			}
		}
		else
			if (info.args[1][0] == '#' || info.args[1][0] == '&')
				_privmsgChannel(client_fd, info, info.args[1]);
			else
				_privmsgUsers(client_fd, info, info.args[1]);
	}
	else
		_clients[client_fd]->sendMessage(ERR_NORECIPIENT(_clients[client_fd]->getNick(), "PRIVMSG"));
}
