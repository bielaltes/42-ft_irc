/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:38:15 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 01:05:19 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// First cmd we need to recieve
// PASS message
//      Command: PASS
//   Parameters: <password>
// if pass fails we should close client program.
void	Server::pass(int static client_fd, cmd_s info)
{
	if (info->argc < 2)
	{
		ERR_NEEDMOREPARAMS(client_fd, command);
		return ;
	}
	if (client exists)
	{
		ERR_ALREADYREGISTERED(client);
		return ;
	}
	if (info->av[1] != SERVER.PASS())
	{
		ERR_PASSWDMISMATCH(client);
	}
	//pass ok, quedem a l'espera de que aquest client ens passi USER.
}

