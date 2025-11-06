/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 19:28:42 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/06 18:11:33 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRC.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int	main(int ac, char **av) {
    /**/
    if (ac != 3){
        std::cout << "Wrong args\nRun: ./ircserv <port> <password>\n";
        return (1);
    }    
	try {
		IRC irc(av[1], av[2]);
        irc.run();
	} catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}