/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:06:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 01:22:49 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// KICK message
//       Command: KICK
//    Parameters: <channel> <user> *( "," <user> ) [<comment>]

void	Server::kick(int static client_fd, cmd_s info)
{
	if (info->params< 3)
	{
		ERR_NEEDMOREPARAMS(client_fd, command);
		return ;
	}
	if (channel no existeix)
	{
		ERR_NOSUCHCHANNEL(nickname, channel_name);
		return ;
	}
	if (no te permisos doperador)
	{
		ERR_CHANOPRIVSNEEDED(client, channel);
		return ;
	}
	if (no existeix lusuari del kick)
	{
		ERR_USERNOTINCHANNEL(client, nick, channel);
		return ;
	}
	if (si el client no esta al canal)
	{
		ERR_NOTONCHANNEL(user_id, channel);
		return ;
	}
	// hem de fer fora a l'usuari pero no es un ban, nomes el fem fora del channel
}

