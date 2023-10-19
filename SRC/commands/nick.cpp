/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 22:38:29 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 00:29:01 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//NOT SURE IF WE CAN SET NICK BEFORE USER CMD USE
// Command: NICK
// Parameters: <nickname>
void	Server::nick(int static client_fd, cmd_s info)
{
	if (info->argc < 2)
	{
		ERR_NONICKNAMEGIVEN(client);
		return ;
	}
	if (nickname contains unallowed characters)
	{
		ERR_ERRONEUSNICKNAME(client, nickname);
		return ;
	}
	if (nickname in use)
	{
		ERR_NICKNAMEINUSE(client, nickname);
		return ;
	}

	// set nickname to this client
	// send message that everything ok and welcome
}

//imo aquest error mai es dona pq mai tenim un altre server o no ho entenc(?)
// ERR_NICKCOLLISION (436) 
//   "<client> <nick> :Nickname collision KILL from <user>@<host>"
// Returned by a server to a client when it detects a nickname collision
// (registered of a NICK that already exists by another server). The text used in the last param of this message may vary.
