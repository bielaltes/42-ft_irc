/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:33:55 by jareste-          #+#    #+#             */
/*   Updated: 2023/11/02 23:07:03 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Server.hpp"

cmd Server::_parse(const char *str, char c)
{
    cmd command;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, c)) {
        command.args.push_back(token);
    }
    return command;
}

std::vector<std::string> Server::_splitByDelimiters(const std::string& input, const std::string& delimiters)
{
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while (start < input.length()) {
        start = input.find_first_not_of(delimiters, end);
        if (start == std::string::npos) {
            break;
        }
        end = input.find_first_of(delimiters, start);
        if (end == std::string::npos) {
            tokens.push_back(input.substr(start));
            break;
        } else {
            tokens.push_back(input.substr(start, end - start));
        }
    }
    return tokens;
}

static bool isEmpty(const std::string& str)
{
    return str.empty();
}

static void removeEmpty(cmd &c)
{
	for (std::vector<std::string>::iterator it = c.args.begin(); it != c.args.end(); )
	{
		if (isEmpty(*it))
		    it = c.args.erase(it);
		else
	    ++it;
	}
}

static bool	checkInit(Client *client, cmd &c)
{
	if (!client->Autenticated() || c.args[0] == "PASS" ||\
	(!client->Registered() && c.args[0] != "USER" && c.args[0] != "NICK"))
		return true;
	return false;
}

void Server::_runCmd(cmd c, int const client_fd)
{
	std::string cmds[10] = {"JOIN", "USER", "NICK", "PRIVMSG",\
	 "INVITE", "TOPIC", "NAMES", "MODE", "KICK", "PING"};
	void	(Server::*f[10])(int const client_fd, cmd &info) = \
	{&Server::_join, &Server::_user, &Server::_nick, &Server::_privmsg,\
	 &Server::_invite, &Server::_topic, &Server::_names,\
	 &Server::_mode, &Server::_kick, &Server::_ping};

	removeEmpty(c);
	if (checkInit(_clients[client_fd], c))
	{
		if (c.args[0] == "PASS")
		{
			_pass(client_fd, c);
			return ;
		}
	}
	else
	{
		for (int i = 0; i < 9; i++)
			if (c.args[.0] == cmds[i])
			{
				(this->*f[i])(client_fd, c);
				return ;
			}
	}
}
