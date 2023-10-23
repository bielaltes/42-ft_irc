/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:58:43 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/23 23:24:35 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

// PRIVMSG message
//      Command: PRIVMSG
//   Parameters: <target>{,<target>} <text to be sent>

void	Server::privmsgChannel(int const client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 
	std::string	nickname = client->getNick();

	if (_searchChannel(info.args[1]) == -1)
	{
		client->sendMessage(ERR_NOSUCHNICK(_clients[client_fd]->getName(), _clients[client_fd]->getNick()));
		return ;
	}
	// if ()//no ho pot enviar al canal, entenc que no te permisos o nose
	// {
	// 	client.sendMessage(ERR_CANNOTSENDTOCHAN(client.getName(), info.args[1]));
	// 	return ;
	// }
	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NOTEXTTOSEND(client->getName()));
		return ;
	}
	int tst = _searchChannel(info.args[1]);
	std::cout << "Sending from client " << nickname << " message "<< info.args[2] << "\n";
	_channels[tst]->sendMsg(*client, info.args[2]);
}

void	Server::privmsgUsers(int const client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 
	std::string	nickname = client->getNick();

	if (info.args[1][0] == ':')
	{
		client->sendMessage(ERR_NORECIPIENT(client->getName(), info.args[1]));
		return ;
	}
	if (!_existsClientNick(info.args[1]))
	{
		client->sendMessage(ERR_NOSUCHNICK(_clients[client_fd]->getName(), _clients[client_fd]->getNick()));
		return ;
	}
	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NOTEXTTOSEND(client->getName()));
		return ;
	}
	int target_fd = _searchUser(info.args[1]);
	if (target_fd != -1)
	{
		Client	*target = _clients[target_fd];
		target->sendMessage(info.args[2]);
	}
}

void	Server::privmsg(int const client_fd, cmd info)
{	
	if (info.args[1][0] == '#' || info.args[1][0] == '&')
		privmsgChannel(client_fd, info);
	else
		privmsgUsers(client_fd, info);
}

// RPL_AWAY (301) ?????????????? 
//   "<client> <nick> :<message>"
// Indicates that the user with the nickname <nick> is currently away and sends the away message that they set.

// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402)
// ERR_CANNOTSENDTOCHAN (404)
// ERR_TOOMANYTARGETS (407)
// ERR_NORECIPIENT (411)
// ERR_NOTEXTTOSEND (412)
// ERR_NOTOPLEVEL (413)
// ERR_WILDTOPLEVEL (414)
// RPL_AWAY (301)