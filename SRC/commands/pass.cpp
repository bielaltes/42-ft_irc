/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:38:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 19:04:07 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"
// First cmd we need to recieve
// PASS message
//      Command: PASS
//   Parameters: <password>
// if pass fails we should close client program.
void	Server::pass(int static client_fd, cmd_s info)
{
	Client		&client = _clients[client_fd]; 
	std::string	nickname = client.getNick();

	if (info->args.size() < 2)
	{
		client.sendMessage(ERR_NEEDMOREPARAMS(client_fd, command));
		return ;
	}
	if (client.getPwd())
	{
		client.sendMessage(ERR_ALREADYREGISTERED(client));
		return ;
	}
	if (info->args[1] != _psswd)
	{
		client.sendMessage(ERR_PASSWDMISMATCH(client));
		remove();//metodo de remove del server
		close(client_fd);
		return ;
	}
	client.setPwd();
	//pass ok, quedem a l'espera de que aquest client ens passi USER.
}

