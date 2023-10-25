/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 02:06:08 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 03:41:42 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//has to display a whole list of names with RPL_NAMREPLY(353) 
//ENDED BY RPL_ENDOFNAMES(471)
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
