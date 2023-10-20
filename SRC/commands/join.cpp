/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:08:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/20 10:14:21 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::join(int const client_fd, cmd info)
{	
	Client		&client = *_clients[client_fd]; 
	std::string	nickname = client.getNick();

	// std::string	channel_name = info.channel_name;
	// std::string	invited_client = info.inv_client_name;


			// if (info.args.size() < 2 || (channel.getK() && info.args.size() < 3))
			// {
			// 	client.SendMessage(ERR_NEEDMOREPARAMS(client_fd, command));
			// 	return ;
			// }
	//COMENTAT PQ DE MOMENT NO POSAREM LIMIT ALS CANALS QUE ES POT UNIR UN USER
	// if (client esta connectat a molts canals) //no se si ho hem de gestionar realment
	// {
	// 	ERR_TOOMANYCHANNELS(nickname, channel);
	// 	return ;
	// }
	
			// if (pass != _channels[ch].getPass())//nook
			// {
			// 	client.SendMessage(ERR_BADCHANNELKEY(client, channel));
			// 	return ;
			// }
	// if (client is banned from chan)
	// {
	// 	ERR_BANNEDFROMCHAN(client, channel);
	// 	return ;
	// }
			// if (client was not invited)//nook
			// {
			// 	client.SendMessage(ERR_INVITEONLYCHAN(client, channel));
			// 	return ;
			// }
			// if (channel == full)//nook
			// {
			// 	client.SendMessage(ERR_CHANNELISFULL(client, channel));
			// 	return ;
			// }
		_addClientToChannel(client_fd, info.args[1]);
		// int ch = _searchChannel(info.args[1]);
			// if (channel has topic)//nook
			// {	
			// 	client.SendMessage(RPL_TOPIC(client, channel, topic)) //S'ENVIA AL CLIENT QUE ACABA D'ENTRAR
			// 	client.SendMessage(RPL_TOPICWHOTIME(client, channel, topic, setat))s //S'ENVIA AL CLIENT TMB DESPUES DE L'ANTERIOR
			// }
			// else
		// client.SendMessage(RPL_NOTOPIC(client_fd, client, _channels));
	// _channels[ch]->sendMsg(client, info.args[2]);//haurem d'avisar a tots que algú s'ha unit
}
