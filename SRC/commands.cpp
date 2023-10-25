/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:33:55 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 17:53:58 by jareste-         ###   ########.fr       */
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

void Server::_runCmd(cmd c, int const client_fd)
{
	if (!_clients[client_fd]->Autenticated() || c.args[0] == "PASS")
	{
		if (c.args[0] == "PASS")
			pass(client_fd, c);
	}
	else
	{
		if (c.args[0] == "JOIN")
		{
			join(client_fd, c);
		}
		if (c.args[0] == "USER")
		{
			user(client_fd, c);
		}
		if (c.args[0] == "NICK")
		{
			nick(client_fd, c);
		}
		if (c.args[0] == "PRIVMSG")
		{
			privmsg(client_fd, c);
		}
		if (c.args[0] == "INVITE")
		{
			invite(client_fd, c);
		}
		if (c.args[0] == "TOPIC")
		{
			topic(client_fd, c);
		}
		if (c.args[0] == "NAMES" && c.args.size() > 1)
		{
			names(client_fd, c);
		}
		if (c.args[0] == "MODE")
		{
			mode(client_fd, c);
		}
		if (c.args[0] == "KICK")
		{
			kick(client_fd, c);
		}
	}
}

std::vector<std::string> Server::_splitByDelimiters(const std::string& input, const std::string& delimiters) {
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