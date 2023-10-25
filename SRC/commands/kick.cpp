/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:06:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 16:34:00 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// KICK message
//       Command: KICK
//    Parameters: <channel> <user> *( "," <user> ) [<comment>]


NO VA
void	Server::kick(int static client_fd, cmd info)
{
	Client		*client = _clients[client_fd]; 

	if (info->args.size() < 3)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS(client->getNick(), info.args[0]));
		return ;
	}

	//je de fet un get del channel o algo.
	int	ch = _searchChannel(info.args[1]);
	if (ch == -1)
	{
		client->sendMessage(ERR_NOSUCHCHANNEL(client->getNick(), info.args[1]));
		return ;
	}
	Channel *channel = _channels[ch];
	if (!channel->isOperator(client_fd))
	{
		client.SendMessage(ERR_CHANOPRIVSNEEDED(client->getNick(), channel->getName()));
		return ;
	}
	if (channel->isMember(args[2]))
	{
		client.SendMessage(ERR_USERNOTINCHANNEL(client->, nick, channel->getName));
		return ;
	}
	if (si el client no esta al canal)
	{
		client.SendMessage(ERR_NOTONCHANNEL(user_id, channel));
		return ;
	}
	channel.kickUser();
	chanel.SendMessage();//avisem a tot el channel de que hem fet fora un usuari.
}


