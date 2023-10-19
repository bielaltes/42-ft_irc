/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baltes-g <baltes-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:38:08 by baltes-g          #+#    #+#             */
/*   Updated: 2023/10/19 14:29:39 by baltes-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Includes.hpp"

class Channel
{
    private:
        bool _i;
        bool _t;
        bool _k;
        bool _o;
        bool _l;

        int limit;
        
        std::string topic = "";
        
        std::map<int, Client *> _members;
        std::map<int, Client *> _invited;
        std::map<int, Client *> _operators;

    public:
        //getters & setters
    
        //functions
        void AddClient(Client &c);
        void RmClient(Client &c);
};
