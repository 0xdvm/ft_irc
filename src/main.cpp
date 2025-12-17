/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:58:05 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/12 20:58:07 by dvemba           ###   ########.fr       */
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