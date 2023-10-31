/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:38:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/31 00:12:07 by jareste-         ###   ########.fr       */
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

void	Server::nick(int const client_fd, cmd &info)
{	
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 2)
	{
		client->sendMessage(ERR_NONICKNAMEGIVEN(client->getNick()));
		return ;
	}
	if (parseNick(info.args[1]))
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
	if (!client->Registered())
	{
		client->setReg();
		client->sendMessage(RPL_WELCOME(client->getNick(), "Jareste.Segfault.BieldidNothing", client->getNick(), client->getHostName()));//nook
		client->sendMessage(RPL_YOURHOST(client->getNick(), "Jareste.Segfault.BieldidNothing"));
		client->sendMessage(RPL_MYINFO(client->getNick(), "Jareste.Segfault.BieldidNothing"));
	}
	else
		client->sendMessage(":" + client->getName() + " NICK " +client->getNick());
}
