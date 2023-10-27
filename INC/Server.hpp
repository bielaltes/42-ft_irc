/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:22:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/27 07:10:42 by jareste-         ###   ########.fr       */
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

        cmd _parse(const char *str, const char c);
        cmd _parse(std::string s, char c);
        void _runCmd(cmd c, int const fd);
        void _newClient();
        void _request(int i);
        int _searchChannel(const std::string &name);
        int _searchUser(const std::string &name);
        void _addClientToChannel(int fd, const std::string &ch_name);
        bool _existsClientNick(const std::string &nick);
        bool _existsClientUser(const std::string &user);
        void _rmClient(const Client &c);
        std::vector<std::string> _splitByDelimiters(const std::string& input, const std::string& delimiters);
        void    join(int const client_fd, cmd info);
        int     joinSingle(int const client_fd, cmd info, std::string target, int pwdNum);
        void    pass(int const client_fd, cmd info);
        void    user(int const client_fd, cmd info);
        void    nick(int const client_fd, cmd info);
        void    privmsg(int const client_fd, cmd info);
        void    privmsgUsers(int const client_fd, cmd info, std::string target_name);
        void    privmsgChannel(int const client_fd, cmd info, std::string target_name);
        void    invite(int const client_fd, cmd info);
        void    topic(int const client_fd, cmd info);
        void    names(int const client_fd, cmd info);
        void    mode(int const client_fd, cmd info);
        void    kick(int const client_fd, cmd info);
        Client  *kickSingle(int const client_fd, std::string target, Channel *channel);
        std::string currentTime();
        cmd  getPwds(cmd info);

    public:
        Server(int port, const std::string &psswd);
        ~Server();

        Client *getClient(int fd);
        
        void LoopServer();
};
