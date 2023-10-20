/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:38:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/20 20:26:56 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"
// First cmd we need to recieve
// PASS message
//      Command: PASS
//   Parameters: <password>
// if pass fails we should close client program.
void	Server::pass(int const client_fd, cmd info)
{
	Client		&client = *_clients[client_fd]; 
	std::string	nickname = client.getNick();

	std::cout << "test" << std::endl;
	if (info.args.size() < 2)
	{
		client.sendMessage(ERR_NEEDMOREPARAMS(_clients[client_fd]->getNick(), info.args[0]));
		return ;
	}
	if (client.getPwd() == true)
	{
		std::cout << "sou tots uns primos" << std::endl; 
		client.sendMessage(ERR_ALREADYREGISTERED(_clients[client_fd]->getNick()));
		return ;
	}
	if (info.args[1] != _psswd)
	{
		std::cout << info.args[1] + "|" << _psswd + "|" << std::endl;
		client.sendMessage(ERR_PASSWDMISMATCH(_clients[client_fd]->getNick()));
		// rmClient(client_fd);//no esta implementat encara
		close(client_fd);
		return ;
	}
	client.setPwd();
}

