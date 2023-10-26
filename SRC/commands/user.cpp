/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:34:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 22:41:56 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::user(int const client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 
	
	if (info.args.size() < 5)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
		return ;
	}
	if (_existsClientUser(info.args[1]))
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
	client->sendMessage(RPL_WELCOME(client->getNick(), "s.IRC.BieldidNothing", client->getNick(), client->getHostName()));//nook
	client->sendMessage(RPL_YOURHOST(client->getNick(), "Jareste.IRC.BieldidNothing"));
	client->sendMessage(RPL_MYINFO(client->getNick(), "Jareste.IRC.BieldidNothing"));
}
