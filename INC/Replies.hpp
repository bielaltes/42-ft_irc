/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:58:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 01:22:47 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//INVITE REPLIES
# define RPL_INVITING(user_id, client, nick, channel) ("RPL : "  + " 341 " + user_id + client + " " + nick + " #" + channel + "\r\n")
# define ERR_NEEDMOREPARAMS(user_id, command) ("ERR : "  + " 461 " + user_id + command + ":Not enough parameters")
# define ERR_NOSUCHCHANNEL(user_id, channel) ("ERR : " + " 403 "  + user_id + channel + ":No such channel")
# define ERR_NOTONCHANNEL(user_id, channel) ("ERR : " + " 442 "  + user_id + channel + ":You're not on that channel")
# define ERR_CHANOPRIVSNEEDED(user_id, channel) ("ERR : " + " 482 "  + user_id + channel + ":You're not channel operator")
# define ERR_USERONCHANNEL(user_id, nick, channel) ("ERR : " + " 443 " + user_id + nick + channel":is already on channel")

//PASS REPLIES
// ERR_NEEDMOREPARAMS (461)
# define ERR_ALREADYREGISTERED(client) ("ERR : " + " 462 " + client + " :You may not reregister")
# define ERR_PASSWDMISMATCH(client) ("ERR : " + " 464 "  + client + " :Password incorrect")

//KICK REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_NOTONCHANNEL (442)
# define ERR_USERNOTINCHANNEL(client, nick, channel) ("ERR : " + " 441 "  + client + nick + channel + " :They aren't on that channel")

//TOPIC REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
# define RPL_NOTOPIC(user_id, client, channel) ("RPL : " + " 331 "  + user_id + client + channel + " :No topic is set")
# define RPL_TOPIC(client, channel, topic) ("RPL : " + " 332 "  + client + channel + topic)
# define RPL_TOPICWHOTIME(client, channel, nick, setat) ("RPL : " + " 333 "  + client + channel + nick + setat)

//MODE REPLIES
//MODE I
# define ERR_INVITEONLYCHAN(client, channel) ("ERR : " + " 473 " + client + channel + " :Cannot join channel (+i)")
# define ERR_INVALIDMODEPARAM(client, target /*chan/user*/, mode, parameter, description) (client + target + mode + parameter + " :" + description)
# define ERR_INVALIDKEY(client, target chan) ("ERR : " + " 525 " + client + target chan + " :Key is not well-formed")
//FALTEN REPLIES


//JOIN REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
# define ERR_TOOMANYCHANNELS(client, channel) ("ERR : " + " 405 " + client + channel + " :You have joined too many channels")
# define ERR_BADCHANNELKEY(client, channel) ("ERR : " + " 475 " + client + channel + " :Cannot join channel (+k)")
# define ERR_BANNEDFROMCHAN(client, channel) ("ERR : " + " 474 " + client + channel + " :Cannot join channel (+b)")
# define ERR_CHANNELISFULL(client, channel) ("ERR : " + " 471 " + client + channel + " :Cannot join channel (+l)")
// ERR_INVITEONLYCHAN (473)
# define ERR_BADCHANMASK(channel) ("ERR : " + " 476 " + channel + " :Bad Channel Mask")
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
# define RPL_NAMREPLY(client, symbol, channel, prefix, nickname) ("RPL : " + " 333 "  + client + symbol + channel + " :[" + prefix + "]" + nickname + "{ [" + prefix + "]"+ nickname)
# define RPL_ENDOFNAMES(client, channel) ("RPL : " + " 333 "  + client + channel + " :End of /NAMES list")

//NICK REPLIES
# define ERR_NONICKNAMEGIVEN(client) ("ERR : " + " 431 " + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nickname) ("ERR : " + " 431 " + client + nickname + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nickname) ("ERR : " + " 433 " + client + nickname + " :Nickname is already in use")
# define ERR_NICKCOLLISION(client, nickname, user, host) ("ERR : " + " 436 " + client + nickname + " :Nickname collision KILL from " + user + "@" + host)

//PASS REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_ALREADYREGISTERED (462)
# define ERR_PASSWDMISMATCH(client) ("ERR : " + " 464 " + client + " :Password incorrect")

