/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:22:24 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/31 12:23:56 by jareste-         ###   ########.fr       */
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

template <typename T>
std::string to_string(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

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
        void    _join(int const client_fd, cmd &info);
        int     _joinSingle(int const client_fd, cmd &info, std::string &target, int pwdNum);
        void    _pass(int const client_fd, cmd &info);
        void    _user(int const client_fd, cmd &info);
        void    _nick(int const client_fd, cmd &info);
        void    _privmsg(int const client_fd, cmd &info);
        void    _privmsgUsers(int const client_fd, cmd &info, std::string &target_name);
        void    _privmsgChannel(int const client_fd, cmd &info, std::string &target_name);
        void    _invite(int const client_fd, cmd &info);
        void    _topic(int const client_fd, cmd &info);
        void    _names(int const client_fd, cmd &info);
        void    _mode(int const client_fd, cmd &info);
        void    _kick(int const client_fd, cmd &info);
        Client  *_kickSingle(int const client_fd, std::string &target, Channel *channel);
        std::string _currentTime();
        cmd  _getPwds(cmd &info);

    public:
        Server(int port, const std::string &psswd);
        ~Server();

        Client *getClient(int fd);
        
        void LoopServer();
};
