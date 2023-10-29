/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:58:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/29 12:40:28 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//INVITE REPLIES
# define RPL_INVITING(client, nick, channel) (std::string("341 ") + client + " " + nick + " " + channel)
# define ERR_NEEDMOREPARAMS(user_id, command) (std::string("461 ") + user_id + " " + command + std::string(" :Not enough parameters"))
# define ERR_NOSUCHCHANNEL(user_id, channel) (std::string("403 ") + user_id + " " +  channel + " :No such channel")
# define ERR_NOTONCHANNEL(user_id, channel) (std::string("442 ") + user_id + " " +  channel + " :You're not on that channel")
# define ERR_CHANOPRIVSNEEDED(user_id, channel) (std::string("482 ") + user_id + " " +  channel + " :You're not channel operator")
# define ERR_USERONCHANNEL(user_id, nick, channel) (std::string("443 ") + user_id + " " +  nick + " " + channel + " :is already on channel")

//PASS REPLIES
// ERR_NEEDMOREPARAMS (461)
# define ERR_ALREADYREGISTERED(client) (std::string("462 ") + client + " :You may not reregister")
# define ERR_PASSWDMISMATCH(client) (std::string("464 ") + client + " :Password incorrect")

//KICK REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_NOTONCHANNEL (442)
# define ERR_USERNOTINCHANNEL(client, nick, channel) (std::string("441 ") + client + " " + nick + " " + channel + " :They aren't on that channel")

//TOPIC REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
# define RPL_NOTOPIC(client, channel) (std::string("331 ") + client + " " + channel + " :No topic is set")
# define RPL_TOPIC(client, channel, topic) (std::string("332 ") + client + " " + channel + " " + topic)
# define RPL_TOPICWHOTIME(client, channel, nick, setat) (std::string("333 ") + client + " " + channel + " " + nick + " " + setat)

//MODE REPLIES
//MODE I
# define ERR_INVITEONLYCHAN(client, channel) (std::string("473 ") + client + " " + channel + " :Cannot join channel (+i)")
// # define ERR_INVALIDKEY(client, target_chan) ("" + " 525 " + client + target chan + " :Key is not well-formed")
//FALTEN REPLIES


//JOIN REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
# define ERR_TOOMANYCHANNELS(client, channel) (std::string("405 ") + client + " " + channel + " :You have joined too many channels")
# define ERR_BADCHANNELKEY(client, channel) (std::string("475 ") + client + " " + channel + " :Cannot join channel (+k)")
# define ERR_BANNEDFROMCHAN(client, channel) (std::string("474 ") + client + channel + " :Cannot join channel (+b)")
# define ERR_CHANNELISFULL(client, channel) (std::string("471 ") + client + " " + channel + " :Cannot join channel (+l)")
// ERR_INVITEONLYCHAN (473)
# define ERR_BADCHANMASK(client) (std::string("476 ") + client + " :Bad Channel Mask")
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
# define RPL_NAMREPLY(client, channel, prefix, nickname) (std::string("353 ") + client + " = " + channel + " :" + prefix  + nickname)
# define RPL_ENDOFNAMES(client, channel) (std::string("366 ") + client + " " + channel + " :End of /NAMES list")

//NICK REPLIES
# define ERR_NONICKNAMEGIVEN(client) (std::string("431 ") + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nickname) (std::string("431 ") + client + " " +  nickname + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nickname) (std::string("433 ") + client + " " + nickname + " :Nickname is already in use")
# define ERR_NICKCOLLISION(client, nickname, user, host) (std::string("436 ") + client + " " +  nickname + " :Nickname collision KILL from " + user + "@" + host)

//PRIVMSG REPLIES
# define ERR_NOSUCHNICK(client, nickname) (std::string("401 ") + client + nickname + " :No suck nick/channel")
# define ERR_CANNOTSENDTOCHAN(client, channel) (std::string("404 ") + client + channel + " :Cannot send to channel")
# define ERR_NORECIPIENT(client, command) (std::string("411 ") + client + " :No recipient given " + command)
# define ERR_NOTEXTTOSEND(client) (std::string("412 ") + client + " :No text to send")
# define RPL_AWAY(client, nick, message) (std::string("301 ") + client + nick + " :" + message)
// ERR_TOOMANYTARGETS (407)
// ERR_NOTOPLEVEL (413)
// ERR_WILDTOPLEVEL (414)

//WELCOME REPLIES
# define RPL_WELCOME(client, networkname, nick, userhost) (std::string("001 ") + client + " :Welcome to the " + networkname + " Network, " + nick + "!" + userhost)
# define RPL_YOURHOST(client, servername) (std::string("002 ") + client + " :Your host is " + servername + ", running version 1.0")
# define RPL_CREATED(client, datetime) (std::string("003 ") + client + " :This server was created " + datetime)
# define RPL_MYINFO(client, servername) (std::string("004 ") + client + " " + servername +  " 1.0 itkol")

//MODE REPLIES
# define RPL_CHANNELMODEIS(client, channel, modestring, arguments) (std::string("324 ") + client + " " + channel + " " + modestring + " " + arguments)
# define ERR_INVALIDMODEPARAM(client, target, mode, parameter, description) (std::string("696 ") + client + " " + target + " " + mode + " " + parameter + " :" + description)
