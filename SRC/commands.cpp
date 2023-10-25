/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:33:55 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 14:34:28 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to redirect each client to a concrete cmd

#include "../INC/Server.hpp"

cmd Server::_parse(const char *str, char c)
{
    cmd command;
    std::stringstream ss(str);
    std::string token;
	std::cout <<"Income str " << str;
    while (std::getline(ss, token, c)) {
        command.args.push_back(token);
    }
	for (size_t i = 0; i < command.args.size(); ++i)
		std::cout << "i: " << command.args[i] << std::endl;
    return command;
}

void Server::_runCmd(cmd c, int const client_fd)
{
	//split input 
	//array de strings amb els noms de les comandes per comparar amb l'input:
	// std::string cmds[] = {"INVITE", "JOIN", "USER", "NICK", "PASS", "MODE", "KICK", "TOPIC", ""};
	// //array de funcions a executar:
	// void	(Server::*execmd[3])(int const client_fd, cmd info) = {&Server::invite, &Server::join, &Server::user};
	if (!_clients[client_fd]->Autenticated() || c.args[0] == "PASS")
	{
		if (c.args[0] == "PASS")
			pass(client_fd, c);
		// if (!_clients[client_fd]->getPwd()) //not sure about
		// {
		// 	// rmClient(client_fd);//no esta implementat encara
		// 	close(client_fd);
		// 	return ;
		// } 
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
		// if (i == 10)//10 is a placeholder
			// NO COMMAND FOUND; //not sure if we have to throw an exception or?
	}
}

std::vector<std::string> Server::_splitByDelimiters(const std::string& input, const std::string& delimiters) {
    std::vector<std::string> tokens;
    size_t start = 0, end = 0;

    while (start < input.length()) {
        // Find the first character that is not a delimiter
        start = input.find_first_not_of(delimiters, end);

        // If no non-delimiter character is found, break
        if (start == std::string::npos) {
            break;
        }

        // Find the end of the token
        end = input.find_first_of(delimiters, start);

        // Extract the token
        if (end == std::string::npos) {
            tokens.push_back(input.substr(start));
            break;
        } else {
            tokens.push_back(input.substr(start, end - start));
        }
    }

    return tokens;
}