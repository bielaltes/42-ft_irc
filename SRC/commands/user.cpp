/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:34:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/20 20:06:32 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::user(int const client_fd, cmd info)
{
	Client		&client = *_clients[client_fd]; 
	
	if (info.args.size() < 4)
	{
		client.sendMessage(ERR_NEEDMOREPARAMS(_clients[client_fd]->getNick(), info.args[0]));
		return ;
	}
	if (_existsClientUser(info.args[1]))//already exists
	{
		client.sendMessage(ERR_ALREADYREGISTERED(_clients[client_fd]->getNick()));
		return ;
	}
	client.setUserName(info.args[1]);
	client.setRealName(info.args[4]);
	if (client.getNick() == "")
		return ;
	client.sendMessage("Welcome you are registered");//nook
	//else  we have to print the repply that everything went welland user is registered.
}

//aquest no hauria de tindre repply ja que e suposa que la repply ve despues d'assignar el nick
//aixi doncs quedem a l'espera de rebre un nickname per acabar registre
