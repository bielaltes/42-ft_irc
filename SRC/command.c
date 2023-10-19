/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:30:09 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 14:32:03 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Includes.hpp"

cmd &Server::_Parse(char *str)
{
    cmd command;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, ' ')) {
        command.args.push_back(token);
    }
}


void Server::_RunCmd(cmd &c, int fd)
{
    if (cmd.args[0] == "PASS")
    {

    }
    else if (cmd.args[0] == "USER")
    {

    }
    else if (cmd.args[0] == "PRIVMSG")
    {

    }
    else
    {
        _clients[fd].SendMessage("TF ARE U DOING");
    }
}
