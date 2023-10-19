/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:34:06 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 01:05:35 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	Server::user(int static client_fd, cmd_s info)
{
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
	// set username as first av;
	// set realname as 4th av;
}

//aquest no hauria de tindre repply ja que e suposa que la repply ve despues d'assignar el nick
//aixi doncs quedem a l'espera de rebre un nickname per acabar registre
