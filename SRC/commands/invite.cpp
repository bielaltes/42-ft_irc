/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:58:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 19:04:24 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// INVITE message
//      Command: INVITE
//   Parameters: <nickname> <channel>
// The INVITE command is used to invite a user to a channel. The parameter <nickname> is the nickname of the person to be invited to the target channel <channel>.

// The target channel SHOULD exist (at least one user is on it). Otherwise, the server SHOULD reject the command with the ERR_NOSUCHCHANNEL numeric.

// Only members of the channel are allowed to invite other users. Otherwise, the server MUST reject the command with the ERR_NOTONCHANNEL numeric.

// Servers MAY reject the command with the ERR_CHANOPRIVSNEEDED numeric. In particular, they SHOULD reject it when the channel has invite-only mode set, and the user is not a channel operator.

// If the user is already on the target channel, the server MUST reject the command with the ERR_USERONCHANNEL numeric.

// When the invite is successful, the server MUST send a RPL_INVITING numeric to the command issuer, and an INVITE message, with the issuer as <source>, to the target user. Other channel members SHOULD NOT be notified.

// Numeric Replies:

// RPL_INVITING (341)
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_USERONCHANNEL (443)
// Command Examples:

//   INVITE Wiz #foo_bar    ; Invite Wiz to #foo_bar
// Message Examples:

//   :dan-!d@localhost INVITE Wiz #test    ; dan- has invited Wiz
//                                         to the channel #test
// Invite list
// Servers MAY allow the INVITE with no parameter, and reply with a list of channels the sender is invited to as RPL_INVITELIST (336) numerics, ending with a RPL_ENDOFINVITELIST (337) numeric.

// Some rare implementations use numerics 346/347 instead of 336/337 as `RPL_INVITELIST`/`RPL_ENDOFINVITELIST`. You should check the server you are using implements them as expected.

// 346/347 now generally stands for `RPL_INVEXLIST`/`RPL_ENDOFINVEXLIST`, used for invite-exception list.
#include "../../INC/Includes.hpp"

void	Server::invite(int static client_fd, cmd info)
{
	Client		&client = _clients(client_fd); 
	std::string	nickname = client.getNick();

	if (nickname.empty() || info->args.size() < 3)
	{
		client.SendMessage(ERR_NEEDMOREPARAMS(nickname, command));
		return ;
	}
	std::string	channel_name = info->args[2];
	std::string	invited_client = info->args[1];

	// aqui he de rebre tots els channels
	int ch_num = searchChannel(channel_name);// me retorna int que equival a la posicio del canal al vector
	//-1 == error.
	if (ch_num == -1)//SEMBLA OK
	{
		client.SendMessage(ERR_NOSUCHCHANNEL(nickname, channel_name));
		return ;
	}
	if (channel.searchNick(client))//NOOK
	{
		client.SendMessage(ERR_NOTONCHANNEL(nickname, channel_name));
		return ;
	}
	if (channel.searchNick(invited_client))//NOOK
	{
		client.SendMessage(ERR_USERONCHANNEL(client_fd, nickname, channel_name));
		return ;
	}
	if (channel mode is inviteonly and user has no priv)//NOOK
	{
		ERR_CHANOPRIVSNEEDED(client_fd, channel_name);
		return ;
	}
	invited_client.SendMessage(RPL_INVITING(client_fd, client.name(), nickname, channel_name));
	return ;
}

