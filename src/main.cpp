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
#include <map>
#include <iostream>
#include <stdexcept>
#include "../inc/utils.hpp"

int	main(int ac, char **av) {
    /**/
    std::string servername = "ircserv";
    std::string port;
    std::string pass;

    if (ac == 3)
    {
        port = av[1];
        pass = av[2];      
    }
    if (ac == 2 && std::string(av[1]) == ".conf")
    {
        try
        {
            std::map<std::string, std::string> list_conf;
            list_conf = extract_conf(&av[1]);
            servername = list_conf["SERVERNAME"];
            port = list_conf["PORT"];
            pass = list_conf["PASS"];
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
            return (1);
        }
    }
    else if (ac != 3)
    {
        std::cout << "Wrong args\nRun: ./ircserv <port> <password>\n";
        return (1);
    }
	try {
		IRC irc(servername, port, pass);
        irc.run();
	} catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}