/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:33:55 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/20 20:40:41 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to redirect each client to a concrete cmd

#include "../INC/Server.hpp"

cmd Server::_parse(const char *str)
{
    cmd command;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ' ')) {
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


	// int i;//definicio fora de l'if per veure si trobem coincidencia o no dins el for.
	// for (i = 0; i < 8;i++)//10 is a placeholder
	// 	if (c.args[0] == cmds[i])
	// 	{
	// 		this->execmd[i](client_fd, c);
	// 		return ;
	// 	}

	// if (c.args[0] == "PASS")
	// {
	// 	pass(client_fd, c);
	// }
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

	// if (i == 10)//10 is a placeholder
		// NO COMMAND FOUND; //not sure if we have to throw an exception or?
}
