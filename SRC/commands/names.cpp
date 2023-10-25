/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:06:08 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 04:03:04 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

void	Server::names(int const client_fd, cmd info)
{
	Client	*client = _clients[client_fd];

	cmd targets = _parse(info.args[1], ',');
	for (unsigned long i = 0; i < targets.args.size(); i++)
	{
		int ch = _searchChannel(targets.args[i]);
		if (ch != -1)
		{
			Channel *channel = _channels[ch];
			channel->sendNames(*client);		
		}
	}
}

void Channel::sendNames(const Client &c) const
{
    Client  *aux;
    for (std::unordered_set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        aux = _s->getClient(*it);
        std::string prefix = "";
        if (isOperator(aux->getFd()))
            prefix = "@";
        sendMsg(NULL, RPL_NAMREPLY(c.getNick(), _name, prefix, aux->getNick()));
    }
   for (std::unordered_set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it) {
        aux = _s->getClient(*it);
        aux->sendMessage(RPL_ENDOFNAMES(aux->getNick(), _name));
    }
}
