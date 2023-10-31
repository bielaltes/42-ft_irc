/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:25:42 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/31 03:33:25 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

static bool	findLetter(std::string const &s, char const c)
{
	if (s == "")
		return false;
	for (unsigned long i = 0; i < s.length(); i++)
		if (s[i] == c)
			return true;
	return false;
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
	std::cout << s.length() << "|" << std::endl;
	for (long long i = s.length() - 1; i >= 0; i--)
	{
		std::cout << i << std::endl;
		if (findLetter("kol", s[i]) && !findLetter(modes["order"] + "+-", s[i]))
			modes["order"] = s[i] + modes["order"];
	}
	std::cout << "+: " << modes["+"] << "|-: " << modes["-"] << "|order: " << modes["order"] << std::endl;
	return modes;
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

static void eraseChar(std::string &str, char c)
{
    for (std::string::iterator it = str.begin(); it != str.end(); ) {
	    if (*it == c) {
	        it = str.erase(it);
	    } else {
	        ++it;
	    }
	}
	// return str;
}

void	Server::mode(int const client_fd, cmd &info)
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
	std::cout << "oleeeee" << std::endl;
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

			int position = orderPosition(modes["order"], 'k');
			switch (position)
			{
				case 0:
				{
					pass = info.args[3];
					break ;
				}
				case 1:
				{
					if (info.args.size() >= 5)
						pass = info.args[4];
					else 
					{
						client->sendMessage(ERR_NEEDMOREPARAMS(\
						client->getNick(), info.args[0] + " +k"));
						eraseChar(modes["+"], 'k');
					}
					break ;
				}
				case 2:
				{
					if (info.args.size() >= 6)
						pass = info.args[5];
					else
					{
						client->sendMessage(ERR_NEEDMOREPARAMS(\
						client->getNick(), info.args[0] + " +k"));
						eraseChar(modes["+"], 'k');
					}
					break ;
				}
			};
			if (findLetter(modes["+"], 'k'))
			{
				channel->setK(true);
				channel->setPass(pass);
			}
		}
		if (findLetter(modes["+"], 'o'))
			channel->setO(true);	
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
			int position = orderPosition(modes["order"], 'l');
			switch (position)
			{
				case 0:
				{
					pass = info.args[3];
					break ;
				}
				case 1:
				{
					if (info.args.size() >= 5)
						pass = info.args[4];
					else 
					{
						client->sendMessage(ERR_NEEDMOREPARAMS(\
						client->getNick(), info.args[0] + " +l"));
						eraseChar(modes["+"], 'l');
					}
					break ;
				}
				case 2:
				{
					if (info.args.size() >= 6)
						pass = info.args[5];
					else
					{
						client->sendMessage(ERR_NEEDMOREPARAMS(\
						client->getNick(), info.args[0] + " +l"));
						eraseChar(modes["+"], 'l');
					}
					break ;
				}
			};
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
			int position = orderPosition(modes["order"], 'k');
			switch (position)
			{
				case 0:
				{
					pass = info.args[3];
					break ;
				}
				case 1:
				{
					if (info.args.size() >= 5)
						pass = info.args[4];
					else 
					{
						client->sendMessage(ERR_NEEDMOREPARAMS(\
						client->getNick(), info.args[0] + " -k"));
						eraseChar(modes["-"], 'k');
					}
					break ;
				}
				case 2:
				{
					if (info.args.size() >= 6)
						pass = info.args[5];
					else
					{
						client->sendMessage(ERR_NEEDMOREPARAMS(\
						client->getNick(), info.args[0] + " -k"));
						eraseChar(modes["-"], 'k');
					}
					break ;
				}
			};
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
			channel->setO(false);	
		if (findLetter(modes["-"], 'l'))
		{
			channel->setL(false);
			channel->setLimit(std::atoi(""));
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
