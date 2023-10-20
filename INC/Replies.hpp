/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Replies.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 19:58:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/20 21:55:10 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

//INVITE REPLIES
# define RPL_INVITING(user_id, client, nick, channel) (std::string("RPL : 341 ") + user_id + client + " " + nick + " #" + channel + "\r\n")
# define ERR_NEEDMOREPARAMS(user_id, command) (std::string("ERR : 461 ") + std::string(user_id) + std::string(command) + std::string(":Not enough parameters") + "\r\n")
# define ERR_NOSUCHCHANNEL(user_id, channel) (std::string("ERR : 403 ") + user_id + channel + ":No such channel" + "\r\n")
# define ERR_NOTONCHANNEL(user_id, channel) (std::string("ERR : 442 ") + user_id + channel + ":You're not on that channel" + "\r\n")
# define ERR_CHANOPRIVSNEEDED(user_id, channel) (std::string("ERR : 482 ") + user_id + channel + ":You're not channel operator" + "\r\n")
# define ERR_USERONCHANNEL(user_id, nick, channel) (std::string("ERR : 443 ") + user_id + nick + channel":is already on channel" + "\r\n")

//PASS REPLIES
// ERR_NEEDMOREPARAMS (461)
# define ERR_ALREADYREGISTERED(client) (std::string("ERR : 462 ") + client + " :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH(client) (std::string("ERR : 464 ") + client + " :Password incorrect" + "\r\n")

//KICK REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_CHANOPRIVSNEEDED (482)
// ERR_NOTONCHANNEL (442)
# define ERR_USERNOTINCHANNEL(client, nick, channel) (std::string("ERR : 441 ") + client + nick + channel + " :They aren't on that channel" + "\r\n")

//TOPIC REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
// ERR_NOTONCHANNEL (442)
// ERR_CHANOPRIVSNEEDED (482)
# define RPL_NOTOPIC(user_id, client, channel) (std::string("RPL : 331 ") + user_id + client + channel + " :No topic is set" + "\r\n")
# define RPL_TOPIC(client, channel, topic) (std::string("RPL : 332 ") + client + channel + topic + "\r\n")
# define RPL_TOPICWHOTIME(client, channel, nick, setat) (std::string("RPL : 333 ") + client + channel + nick + setat + "\r\n")

//MODE REPLIES
//MODE I
# define ERR_INVITEONLYCHAN(client, channel) (std::string("ERR : 473 ") + client + channel + " :Cannot join channel (+i)" + "\r\n")
# define ERR_INVALIDMODEPARAM(client, target /*chan/user*/, mode, parameter, description) (client + target + mode + parameter + " :" + description + "\r\n")
// # define ERR_INVALIDKEY(client, target_chan) ("ERR : " + " 525 " + client + target chan + " :Key is not well-formed")
//FALTEN REPLIES


//JOIN REPLIES
// ERR_NEEDMOREPARAMS (461)
// ERR_NOSUCHCHANNEL (403)
# define ERR_TOOMANYCHANNELS(client, channel) (std::string("ERR : 405 ") + client + channel + " :You have joined too many channels" + "\r\n")
# define ERR_BADCHANNELKEY(client, channel) (std::string("ERR : 475 ") + client + channel + " :Cannot join channel (+k)" + "\r\n")
# define ERR_BANNEDFROMCHAN(client, channel) (std::string("ERR : 474 ") + client + channel + " :Cannot join channel (+b)" + "\r\n")
# define ERR_CHANNELISFULL(client, channel) (std::string("ERR : 471 ")"ERR : " + " 471 " + client + channel + " :Cannot join channel (+l)" + "\r\n")
// ERR_INVITEONLYCHAN (473)
# define ERR_BADCHANMASK(channel) (std::string("ERR : 476 ") + channel + " :Bad Channel Mask" + "\r\n")
// RPL_TOPIC (332)
// RPL_TOPICWHOTIME (333)
# define RPL_NAMREPLY(client, symbol, channel, prefix, nickname) (std::string("RPL : 353 ") + client + symbol + channel + " :[" + prefix + "]" + nickname + "{ [" + prefix + "]"+ nickname + "\r\n")
# define RPL_ENDOFNAMES(client, channel) (std::string("RPL : 366 ") + client + channel + " :End of /NAMES list" + "\r\n")

//NICK REPLIES
# define ERR_NONICKNAMEGIVEN(client) (std::string("ERR : 431 ") + client + " :No nickname given" + "\r\n")
# define ERR_ERRONEUSNICKNAME(client, nickname) (std::string("ERR : 431 ") + client + nickname + " :Erroneus nickname" + "\r\n")
# define ERR_NICKNAMEINUSE(client, nickname) (std::string("ERR : 433 ") + client + nickname + " :Nickname is already in use" + "\r\n")
# define ERR_NICKCOLLISION(client, nickname, user, host) (std::string("ERR : 436 ") + client + nickname + " :Nickname collision KILL from " + user + "@" + host + "\r\n")

//PRIVMSG REPLIES
# define ERR_NOSUCHNICK(client, nickname) (std::string("ERR : 401 ") + client + nickname + " :No suck nick/channel" + "\r\n")
# define ERR_CANNOTSENDTOCHAN(client, channel) (std::string("ERR : 404 ") + client + channel + " :Cannot send to channel" + "\r\n")
# define ERR_NORECIPIENT(client, command) (std::string("ERR : 411 ") + client + " :No recipient given " + command + "\r\n")
# define ERR_NOTEXTTOSEND(client) (std::string("ERR : 412 ") + client + " :No text to send" + "\r\n")
# define RPL_AWAY(client, nick, message) (std::string("RPL : 301 ") + client + nick + " :" + message + "\r\n")
// ERR_TOOMANYTARGETS (407)
// ERR_NOTOPLEVEL (413)
// ERR_WILDTOPLEVEL (414)