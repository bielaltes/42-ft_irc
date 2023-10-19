/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 21:22:00 by jareste-          #+#    #+#             */
/*   Updated: 2023/10/19 19:38:46 by jareste-         ###   ########.fr       */
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
        std::string _username;
        std::string _realname;
        std::string _nick;

    public:
        Client(int fd);
        ~Client();
        bool operator=(const Client & cl);

        void sendMessage(const std::string &s) const;

        bool Autenticated() {return _pswd;}
        bool Registered();

        //getters
        const std::string &getNick() const {return this->_nick;}
        void    setNick(std::string s) {this->_nick = s;}
        const std::string &getName() const {return this->_username;}
        void    setRealName(std::string s) {this->_realname = s;}
        void    setUserName(std::string s)  {this->_username = s;}
        int getFd() const {return this->_fd;}
        
        bool getPwd() const {return _pswd;}
        void setPwd() {_pswd = true;}
        bool getReg() const {return _registered;}
        void setReg() {_registered = true;}
};
