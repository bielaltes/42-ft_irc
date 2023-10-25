/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:25:42 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 10:20:27 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//we have to handle 5 modes, i,t,k,o,l.
//they can be mixed

// MODE message
//      Command: MODE
//   Parameters: <target> [<modestring> [<mode arguments>...]]
// The MODE command is used to set or remove 
// options (or modes) from a given target.
#include "../../INC/Server.hpp"

// void	Server::clientModes(int const client_fd, cmd info)
// {

// }

// void	Server::channelModes(int const client_fd, cmd info)
// {
	
// }

static bool	findLetter(std::string const &s, char const c)
{
	for (unsigned long i = 0; i < s.length(); i++)
		if (s[i] == c)
			return true;
	return false;
}

void	Server::mode(int const client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 

	if (info.args.size() == 1 || (info.args[1][0] != '#' && info.args[1][0] != '&'))
		return ;
	int	ch = _searchChannel(info.args[1]);
	if (ch == -1)
	{
		client->sendMessage(ERR_NOSUCHCHANNEL(client->getNick(), info.args[1]));
		return ;
	}
	Channel	*channel = _channels[ch];
	if (info.args.size() == 2 || (info.args[2][0] != '+' && info.args[2][0] != '-'))
	{
		std::string modes = channel->getModes();
		std::string	arguments = channel->getModeArguments();
		client->sendMessage(RPL_CHANNELMODEIS(client->getNick(), channel->getName(), modes, arguments));
		return ;
	}
	//gestionar si em passen k i l que de moment no ho gestiono
	if (info.args[2][0] == '+')
	{
		if (findLetter(info.args[2], 'i'))
			channel->setI(true);	
		if (findLetter(info.args[2], 't'))
			channel->setT(true);	
		if (findLetter(info.args[2], 'k'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			channel->setK(true);
			channel->setPass(info.args[3]);	
		}
		if (findLetter(info.args[2], 'o'))
			channel->setO(true);	
		if (findLetter(info.args[2], 'l'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			for (unsigned long i = 0; i < info.args[3].length(); i++)
				if (!std::isdigit(info.args[3][i]))
					return ;
			channel->setL(true);
			channel->setLimit(atoi(info.args[3].c_str()));
		}
	}
	else if (info.args[2][0] == '-')
	{
		if (findLetter(info.args[2], 'i'))
			channel->setI(false);	
		if (findLetter(info.args[2], 't'))
			channel->setT(false);	
		if (findLetter(info.args[2], 'k'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			if (info.args[3] != channel->getPass())
				return ;
			channel->setK(false);
			std::string empty = "";
			channel->setPass(empty);	
		}
		if (findLetter(info.args[2], 'o'))
			channel->setO(false);	
		if (findLetter(info.args[2], 'l'))
		{
			channel->setL(false);
			channel->setLimit(atoi(""));
		}
	}
}

// If <modestring> is not given, the RPL_CHANNELMODEIS (324)
//  numeric is returned. Servers MAY choose to hide sensitive 
// information such as channel keys when sending the current
// modes. Servers MAY also return the RPL_CREATIONTIME (329) numeric following RPL_CHANNELMODEIS.

// If <modestring> is given, the user sending the command MUST have 
// appropriate channel privileges on the target channel to change
// the modes given. If a user does not have appropriate privileges 
// to change modes on the target channel, the server MUST NOT 
// process the message, and ERR_CHANOPRIVSNEEDED (482) numeric
// is returned. If the user has permission to change modes on
// the target, the supplied modes will be applied based on 
// the type of the mode (see below). For type A, B, and C 
// modes, arguments will be sequentially obtained from 
// <mode arguments>. If a type B or C mode does not 
// have a parameter when being set, the server MUST 
// ignore that mode. If a type A mode has been sent 
// without an argument, the contents of the list MUST 
// be sent to the user, unless it contains sensitive 
// information the user is not allowed to access. When 
// the server is done processing the modes, a MODE command 
// is sent to all members of the channel containing the mode 
// changes. Servers MAY choose to hide sensitive information when sending the mode changes.
