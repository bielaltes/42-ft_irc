/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:33:55 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 09:50:11 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to redirect each client to a concrete cmd

#include "../INC/Server.hpp"

cmd Server::_parse(const char *str, char c)
{
    cmd command;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, c)) {
        command.args.push_back(token);
    }
   	command.args[command.args.size() -1].erase(command.args[command.args.size() -1].size() -2);
    return command;
}

void Server::_runCmd(cmd c, int const client_fd)
{
	//split input 
	//array de strings amb els noms de les comandes per comparar amb l'input:
	// std::string cmds[] = {"INVITE", "JOIN", "USER", "NICK", "PASS", "MODE", "KICK", "TOPIC", ""};
	// //array de funcions a executar:
	// void	(Server::*execmd[3])(int const client_fd, cmd info) = {&Server::invite, &Server::join, &Server::user};
	if (!_clients[client_fd]->getPwd() || c.args[0] == "PASS")
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

//abans de res he de revisar si estan loguejats, he de revisar si rebo comanda PASS i si
	// client que escriu esta ja loguejat o no.

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
