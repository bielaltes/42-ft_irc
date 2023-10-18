/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:13:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 01:22:42 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  //    Command: TOPIC
  // Parameters: <channel> [<topic>]

void	Server::topic(int static client_fd, cmd_s info)
{
	if (info->argc < 3)
	{
		ERR_NEEDMOREPARAMS(client_fd, command);
		return ;
	}
	if (no existeixchannel)
	{
		ERR_NOSUCHCHANNEL(client_fd, channel);
		return ;
	}
	if (el client no esta al canal)
	{
		ERR_NOTONCHANNEL(client_fd, channel);
		return ;
	}
	if (no te permisos doperador)
	{
		ERR_CHANOPRIVSNEEDED(client_fd, channel);
		return ;
	}
	// set channel topic
	// si no ens passen topic hem de fer clear del topic actual.
}

//aquests 3 s'han d'enviar al entrar a un canal,
// notopic si no hi ha, els altres dos si hi ha topic.
// RPL_NOTOPIC (331)
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)