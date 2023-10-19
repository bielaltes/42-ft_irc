/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 01:06:09 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 15:57:30 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// KICK message
//       Command: KICK
//    Parameters: <channel> <user> *( "," <user> ) [<comment>]

void	Server::kick(int static client_fd, cmd_s info)
{
	Client		&client = _clients(client_fd); 
	std::string	nickname = client.getNick();


	if (info->args.size() < 3)
	{
		client.SendMessage(ERR_NEEDMOREPARAMS(client_fd, command));
		return ;
	}

	//je de fet un get del channel o algo.
	if (channel no existeix)
	{
		client.SendMessage(ERR_NOSUCHCHANNEL(nickname, channel_name));
		return ;
	}
	if (no te permisos doperador)
	{
		client.SendMessage(ERR_CHANOPRIVSNEEDED(client, channel));
		return ;
	}
	if (no existeix lusuari del kick)
	{
		client.SendMessage(ERR_USERNOTINCHANNEL(client, nick, channel));
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


