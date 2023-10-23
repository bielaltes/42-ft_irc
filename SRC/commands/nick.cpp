/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:38:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/23 23:40:44 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

//NOT SURE IF WE CAN SET NICK BEFORE USER CMD USE
// Command: NICK
// Parameters: <nickname>
static bool	parseNick(std::string nick)
{
	std::size_t found = nick.find_first_not_of(NICK_ALLOWED_CH);
	if (found != std::string::npos)
		return true;
	return false;
}

void	Server::nick(int const client_fd, cmd info)
{	
	Client		&client = *_clients[client_fd]; 
	std::string	nickname = client.getNick();

	(void) info;
	if (info.args.size() < 2)
	{
		client.sendMessage(ERR_NONICKNAMEGIVEN(_clients[client_fd]->getNick()));
		return ;
	}
	if (parseNick(nickname))
	{
		client.sendMessage(ERR_ERRONEUSNICKNAME(_clients[client_fd]->getName(), info.args[1]));
		return ;
	}
	if (_existsClientNick(info.args[1]))//nook POTSER ARA SIOK hehe
	{
		client.sendMessage(ERR_NICKNAMEINUSE(_clients[client_fd]->getName(), info.args[1]));
		return ;
	}
	client.setNick(info.args[1]);
	if (client.getName() == "")
		return ;
	client.sendMessage("Welcome you are registered");//nook
	//we must check if username and realname already exist, then 
	// send message that everything ok and welcome
	//otherwise just wait
}

//imo aquest error mai es dona pq mai tenim un altre server o no ho entenc(?)
// ERR_NICKCOLLISION (436) 
//   "<client> <nick> :Nickname collision KILL from <user>@<host>"
// Returned by a server to a client when it detects a nickname collision
// (registered of a NICK that already exists by another server). The text used in the last param of this message may vary.
