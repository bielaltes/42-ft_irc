/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:06:08 by jareste-          #+#    #+#             */
/*   Updated: 2023/11/02 09:32:33 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Server.hpp"

void	Server::_names(int const client_fd, cmd &info)
{
	Client	*client = _clients[client_fd];

	cmd targets = _parse(info.args[1], ',');
	for (unsigned long i = 0; i < targets.args.size(); i++)
	{
		int ch = _searchChannel(targets.args[i]);
		if (ch != -1)
		{
			Channel *channel = _channels[ch];
			channel->_sendNames(*client);		
		}
	}
}

void Channel::_sendNames(const Client &c) const
{
    Client  *aux;
    c.sendMessage(RPL_NAMREPLY(c.getNick(), _name, "", "SegfaultBot"));
    for (std::set<int>::const_iterator it = _members.begin(); it != _members.end(); ++it)
    {
        aux = _s->getClient(*it);
        std::string prefix = "";
        if (isOperator(aux->getFd()))
            prefix = "@";
        c.sendMessage(RPL_NAMREPLY(c.getNick(), _name, prefix, aux->getNick()));
    }
    c.sendMessage(RPL_ENDOFNAMES(c.getNick(), _name));
}
