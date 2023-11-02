/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:25:42 by jareste-          #+#    #+#             */
/*   Updated: 2023/11/02 11:16:03 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

static int	orderPosition(std::string &s, char c);

static bool	findLetter(std::string const &s, char const c)
{
	if (s == "")
		return false;
	for (unsigned long i = 0; i < s.length(); i++)
		if (s[i] == c)
			return true;
	return false;
}

static void eraseChar(std::string &str, char c)
{
    for (std::string::iterator it = str.begin(); it != str.end(); )
    {
	    if (*it == c) {
	        it = str.erase(it);
	    } else {
	        ++it;
	    }
	}
}

static std::map<std::string, std::string> parseMode(std::string &s)
{
	std::map<std::string, std::string> modes;
	int	repeated;
	char c = s[0];

	modes["+"] = "+";
	modes["-"] = "-";
	for (unsigned long i = 0; i < s.length(); i++)
	{
		repeated = 0;
		if (std::isalpha(s[i]) && findLetter("itkol", s[i]))
		{
			for (unsigned long j = i + 1; j < s.length(); j++)
				if (i != j && s[i] == s[j])
					repeated = 1;
			if (repeated == 0 && c == '+')
				modes["+"] = modes["+"] + s[i];
			if (repeated == 0 && c == '-')
				modes["-"] = modes["-"] + s[i];
		}
		if (s[i] == '+' || s[i] == '-')
			c = s[i];
	}
	modes["order"] = "";
	if (s.length() == 0)
		return modes;
	for (long long i = s.length() - 1; i >= 0; i--)
	{
		if (findLetter("kol", s[i]) && !findLetter(modes["order"] + "+-", s[i]))
			modes["order"] = s[i] + modes["order"];
	}
	if (findLetter(modes["-"], 'l') && findLetter(modes["order"], 'l'))
		eraseChar(modes["order"], 'l');
	return modes;
}

static std::string getKey(std::map<std::string, std::string> &modes, cmd &info, char c, Client *client)
{
	std::string key = "";

	int position = orderPosition(modes["order"], c);
	switch (position)
	{
		case 0:
		{
			key = info.args[3];
			break ;
		}
		case 1:
		{
			if (info.args.size() >= 5)
				key = info.args[4];
			else 
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(\
				client->getNick(), info.args[0] + " +" + c));
				eraseChar(modes["+"], '-');
			}
			break ;
		}
		case 2:
		{
			if (info.args.size() >= 6)
				key = info.args[5];
			else
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(\
				client->getNick(), info.args[0] + " +" + c));
				eraseChar(modes["+"], 'o');
			}
			break ;
		}
	};
	return key;
}

static int	orderPosition(std::string &s, char c)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] == c)
			return i;
		i++;
	}
	return i;
}

void	Server::_mode(int const client_fd, cmd &info)
{
	Client		*client = _clients[client_fd]; 
	std::string pass;

	if (info.args.size() == 1 || (info.args[1][0] != '#' && info.args[1][0] != '&'))
	{
		std::string nochanmsg;
		if (info.args.size() > 1)
			nochanmsg = info.args[1];
		else
			nochanmsg = "";
		client->sendMessage(ERR_NOSUCHCHANNEL(client->getNick(), nochanmsg));
		return ;
	}
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
	std::map<std::string, std::string> modes = parseMode(info.args[2]);
	if (modes["+"].size() > 1)
	{
		if (findLetter(modes["+"], 'i'))
			channel->setI(true);	
		if (findLetter(modes["+"], 't'))
			channel->setT(true);	
		if (findLetter(modes["+"], 'k'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			pass = getKey(modes, info, 'k', client);
			if (findLetter(modes["+"], 'k'))
			{
				channel->setK(true);
				channel->setPass(pass);
			}
		}
		if (findLetter(modes["+"], 'o'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			pass = getKey(modes, info, 'k', client);
			if (findLetter(modes["+"], 'o'))
			{
				int	target_fd = _searchUser(pass);
				if (target_fd != -1 && channel->isMember(pass) && channel->isOperator(client_fd))
				{
					Client *target = _clients[target_fd];
					channel->addOperator(*target);
				}
				else if (!channel->isOperator(client_fd))
				{
					client->sendMessage(ERR_CHANOPRIVSNEEDED(\
					client->getNick(), channel->getName()));
					eraseChar(modes["+"], 'o');
				}
				else if (!channel->isMember(pass))
				{
					client->sendMessage(ERR_USERNOTINCHANNEL(\
					client->getNick(), pass, channel->getName()));
					eraseChar(modes["+"], 'o');
				}
			}
		}
		if (findLetter(modes["+"], 'l'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			for (unsigned long i = 0; i < info.args[3].length(); i++)
				if (!std::isdigit(info.args[3][i]))
					return ;
			pass = getKey(modes, info, 'k', client);
			if (findLetter(modes["+"], 'l'))
			{
				if (std::atoi(pass.c_str()) == 0)
					channel->setLimit(1);
				else
					channel->setLimit(std::atoi(pass.c_str()));
				channel->setL(true);
			}
		}
	}
	if (modes["-"].size() > 1)
	{
		if (findLetter(modes["-"], 'i'))
			channel->setI(false);	
		if (findLetter(modes["-"], 't'))
			channel->setT(false);	
		if (findLetter(modes["-"], 'k'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			pass = getKey(modes, info, 'k', client);
			if (findLetter(modes["-"], 'k'))
			{	
				if (pass != channel->getPass())
				{
					client->sendMessage(ERR_INVALIDMODEPARAM(client->getNick()\
					, " MODE ", channel->getName(), "-k", info.args[3]));
					return ;
				}
				channel->setK(false);
				std::string empty = "";
				channel->setPass(empty);	
			}
		}
		if (findLetter(modes["-"], 'o'))
		{
			if (info.args.size() < 4)
			{
				client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
				return ;
			}
			pass = getKey(modes, info, 'k', client);
			if (findLetter(modes["-"], 'o'))
			{
				int	target_fd = _searchUser(pass);
				if (target_fd != -1 && channel->isMember(pass) && channel->isOperator(client_fd))
				{
					Client *target = _clients[target_fd];
					channel->rmOperator(*target);
				}
				else if (!channel->isOperator(client_fd))
				{
					client->sendMessage(ERR_CHANOPRIVSNEEDED(\
					client->getNick(), channel->getName()));
					eraseChar(modes["-"], 'o');
				}
				else if (!channel->isMember(pass))
				{
					client->sendMessage(ERR_USERNOTINCHANNEL(\
					client->getNick(), pass, channel->getName()));
					eraseChar(modes["-"], 'o');
				}
			}
		}
		if (findLetter(modes["-"], 'l'))
		{
			channel->setL(false);
			channel->setLimit(0);
		}
	}
	if ((modes["+"].size() + modes["-"].size()) == 2)
		return ;
	std::string modeActivated = ":" + client->getNick() + "!" + \
	client->getHostName() + " MODE " + channel->getName() + " ";
	if (modes["+"].size() > 1)
		modeActivated.append(modes["+"]);
	if (modes["-"].size() > 1)
		modeActivated.append(modes["-"]);
	channel->sendMsg(NULL, modeActivated);
}
