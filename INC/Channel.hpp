/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:38:08 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 16:00:37 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Includes.hpp"

class Channel
{
    private:
        std::string _name;

        bool _i;
        bool _t;
        bool _k;
        bool _o;
        bool _l;

        int limit;
        
        std::string topic;
        
        std::map<int, Client *> _members;
        std::unordered_set<std::string> _invited;
        std::unordered_set<std::string> _operators;

    public:
        Channel(const std::string &name);
        ~Channel();

        //getters & setters
        const std::string &getName();
        //functions
        void AddClient(Client &c);
        void RmClient(Client &c);

        void SendMsg(Client &c, const std::string &msg);

        bool isMember(std::string &nick);

        void invite(Client &c);


};
