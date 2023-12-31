/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:38:08 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/31 13:06:25 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Includes.hpp"

class Server;

class Channel
{
    private:
        Server *_s;
        std::string _name;

        std::string _pass;
        bool _i;
        bool _t;
        bool _k;
        bool _o;
        bool _l;

        int _limit;
        
        std::string _topic;
        
        std::set<int> _members;
        std::set<int> _invited;
        std::set<int> _operators;

    public:
        Channel(Server *s, const std::string &name, const Client &c);
        ~Channel();

        //getters & setters
        const std::string &getName(){return this->_name;}
        const std::string &getPass(){return this->_pass;}
        bool    getI(){return this->_i;}
        void    setI(bool mode){this->_i = mode;}
        bool    getT(){return this->_t;}
        void    setT(bool mode){this->_t = mode;}
        bool    getK(){return this->_k;}
        void    setK(bool mode){this->_k = mode;}
        void    setPass(std::string &key){this->_pass = key;}
        bool    getO(){return this->_o;}
        void    setO(bool mode){this->_o = mode;}
        bool    getL(){return this->_l;}
        void    setL(bool mode){this->_l = mode;}
        void    setLimit(int n){this->_limit = n;}
        std::string getModes();
        std::string getModeArguments();
        int    getLimit(){return this->_limit;}
        int    getUsersNumber(){return (int)this->_members.size();}
        void    setTopic(std::string const &s){this->_topic = s;}
        const std::string    getTopic(){return this->_topic;}
        //functions
        void    addClient(const Client &c);
        void    rmClient(const Client &c);
        void    addOperator(const Client &c);
        void    rmOperator(const Client &c);

        void    sendMsg(const Client &c, const std::string &msg) const;

        bool    isMember(const std::string &nick);

        void    invite(const Client &c);
        bool    isInvited(const int client_fd) const;
        bool    isOperator(const int client_fd) const;
        void    _sendNames(const Client &c) const;
};
