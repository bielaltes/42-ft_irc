/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:58:10 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/18 18:30:11 by jareste-         ###   ########.fr       */
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

void	invite(Server &server, int static client_fd, cmd_s info)
{
	Client		&client = getClient(server, client_fd); //need to create a getter for client from the server.
	std::string	nickname = client.getNickname();
	std::string	channel_name = info->channel_name;
	std::string	invited_client = info->inv_client_name;

	if (nickname.empty() || channel_name.empty())
	{
		ERR_NEEDMOREPARAMS(nickname, command);
		return ;
	}
	// aqui he de rebre tots els channels
	
	if (channel_name no existeix)
	{
		ERR_NOSUCHCHANNEL(nickname, channel_name);
		return ;
	}
	if (nickname no esta al canal)
	{
		ERR_NOTONCHANNEL(nickname, channel_name);
		return ;
	}
	if (invited_client esta al canal)
	{
		ERR_USERONCHANNEL(client_fd, nickname, channel_name);
		return ;
	}
	if (si client no te permis dinvitació)
	{
		ERR_CHANOPRIVSNEEDED(client_fd, channel_name);
		return ;
	}
	// aqui considerem que ja tot es ok
	RPL_INVITING(client_fd, client.name(), nickname, channel_name);

	// hem invitat al nou user al canal hem de veure si accepta.
}

