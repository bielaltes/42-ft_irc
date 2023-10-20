/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 18:58:43 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/20 10:21:37 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

// PRIVMSG message
//      Command: PRIVMSG
//   Parameters: <target>{,<target>} <text to be sent>

void	Server::privmsg(int const client_fd, cmd info)
{	
	Client		*client = _clients[client_fd]; 
	std::string	nickname = client->getNick();
	// Client		&target = //necessito un getter per al target.

	int tst = _searchChannel(info.args[1]);
	std::cout << "Sending from client " << nickname << " message "<< info.args[2] << "\n";
	_channels[tst]->sendMsg(*client, info.args[2]);
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