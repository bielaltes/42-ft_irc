/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:38:08 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/20 19:52:38 by jareste-         ###   ########.fr       */
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

        bool _i;
        bool _t;
        bool _k;
        bool _o;
        bool _l;

        //int limit =0;
        
        std::string topic;
        
        std::unordered_set<int> _members;
        std::unordered_set<int> _invited;
        std::unordered_set<int> _operators;

    public:
        Channel(Server *s, const std::string &name, const Client &c);
        ~Channel();

        //getters & setters
        const std::string &getName(){return this->_name;}
        //functions
        void addClient(const Client &c);
        void rmClient(const Client &c);

        void sendMsg(const Client &c, const std::string &msg) const;

        bool isMember(const std::string &nick);

        void invite(const Client &c);


};
