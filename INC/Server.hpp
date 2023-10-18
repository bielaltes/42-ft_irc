/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:22:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/18 18:29:51 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include "Includes.hpp"

class Client;
typedef struct cmd
{
    std::vector<std::string> args;
};

class Server
{
    private:
        std::vector<pollfd> _pollsfd;
        std::string _psswd;
        int _port;
        int _active;
        struct pollfd _serverfd;
        std::map<int, Client*> _clients;

        cmd &_Parse(char *str);
        char *_RunCmd(cmd &c, int fd);
        void _NewClient();
        void _Request(int i);

    public:
        Server(int port, std::string psswd);
        ~Server();


        void LoopServer();
};