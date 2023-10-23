/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:22:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/23 22:46:43 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#pragma once
#include "Includes.hpp"

class Client;
class Channel;
typedef struct cmd
{
    std::vector<std::string> args;
} cmd;

class Server
{
    private:
        std::vector<pollfd> _pollsfd;
        std::string _psswd;
        int _port;
        int _active;
        struct pollfd _serverfd;
        std::map<int, Client*> _clients;
        std::vector<Channel *> _channels;

        cmd _parse(const char *str);
        void _runCmd(cmd c, int const fd);
        void _newClient();
        void _request(int i);
        int _searchChannel(const std::string &name);
        int _searchUser(const std::string &name);
        void _addClientToChannel(int fd, const std::string &ch_name);
        bool _existsClientNick(const std::string &nick);
        bool _existsClientUser(const std::string &user);
        void    join(int const client_fd, cmd info);
        void    pass(int const client_fd, cmd info);
        void    user(int const client_fd, cmd info);
        void    nick(int const client_fd, cmd info);
        void    privmsg(int const client_fd, cmd info);
        void    privmsgUsers(int const client_fd, cmd info);
        void    privmsgChannel(int const client_fd, cmd info);
        void    invite(int const client_fd, cmd info);
    public:
        Server(int port, const std::string &psswd);
        ~Server();

        Client *getClient(int fd);
        
        void LoopServer();
};
