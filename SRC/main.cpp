/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:06:33 by baltes-g          #+#    #+#             */
/*   Updated: 2023/11/02 09:11:58 by jareste-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/Includes.hpp"


int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
		return (-1);
    }
    Server s(atoi(argv[1]), std::string(argv[2]));
    try
    {
        s.LoopServer();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }    
}

