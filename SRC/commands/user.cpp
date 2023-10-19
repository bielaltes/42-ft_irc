/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:34:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 19:04:12 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::user(int static client_fd, cmd_s info)
{
	Client		&client = _clients[client_fd]; 
	
	if (info->argc < 4)
	{
		ERR_NEEDMOREPARAMS(client, command);
		return ;
	}
	if (client already exists)
	{
		ERR_ALREADYREGISTERED(client);
		return ;
	}
	client.setUserName(info->args[1]);
	client.setRealName(info->args[4]);
	if (client.getNick() == NULL)
		return ;
	//else  we have to print the repply that everything went welland user is registered.
}

//aquest no hauria de tindre repply ja que e suposa que la repply ve despues d'assignar el nick
//aixi doncs quedem a l'espera de rebre un nickname per acabar registre
