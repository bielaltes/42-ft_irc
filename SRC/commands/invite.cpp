/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:58:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/24 01:13:32 by jareste-         ###   ########.fr       */
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

void	Server::invite(int client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 

	if (info.args.size() < 3)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
		return ;
	}
	std::string	channel_name = info.args[2];
	std::string	invited_client = info.args[1];
	std::string s_client_fd = std::to_string(client_fd);

	int ch_num = _searchChannel(channel_name);
	if (ch_num == -1)
	{
		client->sendMessage(ERR_NOSUCHCHANNEL(client->getNick(), channel_name));
		return ;
	}
	if (!_channels[ch_num]->isMember(client->getNick()))
	{
		client->sendMessage(ERR_NOTONCHANNEL(client->getNick(), channel_name));
		return ;
	}
	if (_channels[ch_num]->isMember(invited_client))
	{
		client->sendMessage(ERR_USERONCHANNEL(s_client_fd, client->getNick(), channel_name));
		return ;
	}
	// if (channel mode is inviteonly and user has no priv)//NOOK
	// {
	// 	ERR_CHANOPRIVSNEEDED(client_fd, channel_name);
	// 	return ;
	// }

	int target_fd = _searchUser(invited_client);
	if (target_fd != -1)
	{
		Client	*target = _clients[target_fd];
		target->sendMessage(":" + client->getNick() + " INVITE " + target->getNick() + channel_name);
		client->sendMessage(RPL_INVITING(client->getNick(), target->getNick(), channel_name));
	}
	return ;
}

