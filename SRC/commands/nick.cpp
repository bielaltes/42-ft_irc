/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:38:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/24 23:13:16 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

static bool	parseNick(std::string nick)
{
	std::size_t found = nick.find_first_not_of(NICK_ALLOWED_CH);
	if (found != std::string::npos)
		return true;
	return false;
}

void	Server::nick(int const client_fd, cmd info)
{	
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 2)
	{
		client->sendMessage(ERR_NONICKNAMEGIVEN(client->getNick()));
		return ;
	}
	if (parseNick(client->getNick()))
	{
		client->sendMessage(ERR_ERRONEUSNICKNAME(client->getName(), info.args[1]));
		return ;
	}
	if (_existsClientNick(info.args[1]))
	{
		client->sendMessage(ERR_NICKNAMEINUSE(client->getName(), info.args[1]));
		return ;
	}
	client->setNick(info.args[1]);
	if (client->getName() == "")
		return ;
	client->sendMessage(RPL_WELCOME(client->getNick(), "Jareste.IRC.BieldidNothing", client->getNick(), client->getHostName()));//nook
	client->sendMessage(RPL_YOURHOST(client->getNick(), "Jareste.IRC.BieldidNothing"));
	client->sendMessage(RPL_MYINFO(client->getNick(), "Jareste.IRC.BieldidNothing"));
}
