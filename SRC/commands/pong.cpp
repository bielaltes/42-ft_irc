/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:40:02 by jareste-          #+#    #+#             */
/*   Updated: 2023/11/03 00:55:02 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/Includes.hpp"

void	Server::_pong(int const client_fd, std::string token)
{
	Client		*client = _clients[client_fd]; 	 

	client->sendMessage("PONG Jareste.Segfault.BieldidNothing " + token);
}
