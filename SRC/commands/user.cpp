/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:34:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/24 23:10:01 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::user(int const client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 
	
	if (info.args.size() < 4)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
		return ;
	}
	if (_existsClientUser(info.args[1]))//already exists
	{
		client->sendMessage(ERR_ALREADYREGISTERED(client->getNick()));
		return ;
	}
	client->setUserName(info.args[1]);
	client->setRealName(info.args[4]);
	std::string hostname = client->getName() + "@127.0.0.1";
	client->setHostName(hostname); 
	if (client->getNick() == "")
		return ;
	client->sendMessage(RPL_WELCOME(client->getNick(), "Jareste.IRC.BieldidNothing", client->getNick(), client->getHostName()));//nook
	client->sendMessage(RPL_YOURHOST(client->getNick(), "Jareste.IRC.BieldidNothing"));
	client->sendMessage(RPL_MYINFO(client->getNick(), "Jareste.IRC.BieldidNothing"));
}

//aquest no hauria de tindre repply ja que e suposa que la repply ve despues d'assignar el nick
//aixi doncs quedem a l'espera de rebre un nickname per acabar registre

// 001 JARESTE :Welcome to the irc.42.Barcelona Network, JARESTE!JARESTE@127.0.0.1
// 002 JARESTE :Your host is irc.42.Barcelona, running version 1.0
// 004 JARESTE irc.42.Barcelona 1.0 ioOw beliIkmstn