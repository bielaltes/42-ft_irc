/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:22:00 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/25 17:47:20 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Includes.hpp"

class Client
{
    private:
        bool _pswd;
        bool _registered;
        int _fd;
        std::string _buffer;
        std::string _username;
        std::string _realname;
        std::string _nick;
        std::string _hostname;

    public:
        Client(int fd);
        ~Client();
        bool operator=(const Client & cl);

        void sendMessage(const std::string &s) const;

        //setters
        void    setNick(std::string s) {this->_nick = s;}
        void    setRealName(std::string s) {this->_realname = s;}
        void    setUserName(std::string s)  {this->_username = s;}
        void    setHostName(std::string s)  {this->_hostname = s;}
        void    setBuffer(std::string s)  {this->_buffer = s;}

        //getters
        const std::string &getNick() const {return this->_nick;}
        const std::string &getName() const {return this->_username;}
        const std::string &getHostName() const {return this->_hostname;}
        const std::string &getBuffer() const {return this->_buffer;}
        int getFd() const {return this->_fd;}        
        void setPwd() {_pswd = true;}
        bool Autenticated() {return _pswd;}
        void setReg() {_registered = true;}
        bool Registered() {return _registered;}
};
