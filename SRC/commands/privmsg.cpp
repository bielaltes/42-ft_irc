/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:58:43 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 19:04:02 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

// PRIVMSG message
//      Command: PRIVMSG
//   Parameters: <target>{,<target>} <text to be sent>

void	Server::privmsg(int const client_fd, cmd_s info)
{	
	Client		&client = _clients[client_fd]; 
	std::string	nickname = client.getNick();
	Client		&target = //necessito un getter per al target.

	target.SendMessage(info->args[2]);
}


// ERR_NOSUCHNICK (401)
// ERR_NOSUCHSERVER (402)
// ERR_CANNOTSENDTOCHAN (404)
// ERR_TOOMANYTARGETS (407)
// ERR_NORECIPIENT (411)
// ERR_NOTEXTTOSEND (412)
// ERR_NOTOPLEVEL (413)
// ERR_WILDTOPLEVEL (414)
// RPL_AWAY (301)