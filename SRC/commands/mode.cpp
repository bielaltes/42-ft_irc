/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:25:42 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 17:07:35 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

static bool	findLetter(std::string const &s, char const c)
{
	for (unsigned long i = 0; i < s.length(); i++)
		if (s[i] == c)
			return true;
	return false;
}

static std::vector<std::string> parseMode(std::string s)
{
	std::vector<std::string> modes;
	int	repeated;
	char c = s[0];

	modes.push_back("+");
	modes.push_back("-");
	for (unsigned long i = 0; i < s.length(); i++)
	{
		repeated = 0;
		if (std::isalpha(s[i]))
		{
			for (unsigned long j = i + 1; j < s.length(); j++)
				if (i != j && s[i] == s[j])
					repeated = 1;
			if (repeated == 0 && c == '+')
				modes[0] = modes[0] + s[i];
			if (repeated == 0 && c == '-')
				modes[1] = modes[1] + s[i];
		}
		if (s[i] == '+' || s[i] == '-')
			c = s[i];
	}
	std::string lastword = "";
	for (unsigned long i = 0; i < s.length(); i++)
	{
		if (s[i] == 'l')
			lastword = s[i];
		if (s[i] == 'k')
			lastword = s[i];
	}
	modes.push_back(lastword);
	return modes;
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
		client->sendMessage(RPL_CHANNELMODEIS(client->getNick(),\
		channel->getName(), modes, arguments));
		return ;
	}
	std::vector<std::string>modes = parseMode(info.args[2]);
	if (modes[0].size() > 1)
	{
		if (findLetter(modes[0], 'i'))
			channel->setI(true);	
		if (findLetter(modes[0], 't'))
			channel->setT(true);	
		if (findLetter(modes[0], 'k'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			channel->setK(true);
			std::string pass;
			if (modes[2] == "k" && findLetter(modes[0], 'l'))
			{
				pass = info.args[4];
			}
			else
				pass = info.args[3];
			channel->setPass(pass);	
		}
		if (findLetter(modes[0], 'o'))
			channel->setO(true);	
		if (findLetter(modes[0], 'l'))
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
			std::string pass;
			if (modes[2] == "l" && findLetter(modes[0], 'k'))
			{
				pass = info.args[4];
			}
			else
				pass = info.args[3];
			channel->setLimit(atoi(pass.c_str()));
		}
	}
	if (modes[1].size() > 1)
	{
		if (findLetter(modes[1], 'i'))
			channel->setI(false);	
		if (findLetter(modes[1], 't'))
			channel->setT(false);	
		if (findLetter(modes[1], 'k'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			if (info.args[3] != channel->getPass())
			{
				client->sendMessage(ERR_INVALIDMODEPARAM(client->getNick()\
				, " MODE ", channel->getName(), "-k", info.args[3]));
				return ;
			}
			channel->setK(false);
			std::string empty = "";
			channel->setPass(empty);	
		}
		if (findLetter(modes[1], 'o'))
			channel->setO(false);	
		if (findLetter(modes[1], 'l'))
		{
			channel->setL(false);
			channel->setLimit(atoi(""));
		}
	}
	std::string modeActivated = ":" + client->getNick() + "!" + \
	client->getHostName() + "MODE" + channel->getName() + " ";
	if (modes[0].size() > 1)
		modeActivated.append(modes[0]);
	if (modes[1].size() > 1)
		modeActivated.append(modes[1]);
	channel->sendMsg(NULL, modeActivated);
}
