/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:08:39 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 01:22:51 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


std::string	Server::join(int static client_fd, cmd_s info)
{	
	Client		&client = getClient(client_fd); 
	std::string	nickname = client.getNickname();
	std::string	channel_name = info->channel_name;
	std::string	invited_client = info->inv_client_name;

	if (info->params< 2 || channel esta en pwd mode && info params < 3)
	{
		ERR_NEEDMOREPARAMS(client_fd, command);
		return ;
	}
	//rebo tota la llista de channels
	if (no existeix el canal)
	{
		ERR_NOSUCHCHANNEL(nickname, channel_name);
		return ;
	}
	if (client esta connectat a molts canals) //no se si ho hem de gestionar realment
	{
		ERR_TOOMANYCHANNELS(nickname, channel);
		return ;
	}
	if (pass != channel.pass)
	{
		ERR_BADCHANNELKEY(client, channel);
		return ;
	}
	if (client is banned from chan)
	{
		ERR_BANNEDFROMCHAN(client, channel);
		return ;
	}
	if (client was not invited)
	{
		ERR_INVITEONLYCHAN(client, channel);
		return ;
	}
	if (channel == full)
	{
		ERR_CHANNELISFULL(client, channel);
		return ;
	}
	RPL_TOPIC(client, channel, topic) //S'ENVIA AL CLIENT QUE ACABA D'ENTRAR
	RPL_TOPICWHOTIME(client, channel, topic, setat) //S'ENVIA AL CLIENT TMB DESPUES DE L'ANTERIOR
	//Hem d'enviar a tots els clients conectats al canal que un nou client s'ha unit
}

