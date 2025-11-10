/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:52:08 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/10 10:55:48 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.hpp"
#include <sstream>

void cmd_start(Client& client, std::string cmd, int size_args){
    (void)size_args;
    (void)cmd;
    
    if (cmd == "CAP" && !client.isAuthenticated()){
        std::cout << ":irc.server: CAP * LS :" << std::endl;
    }
    else{
        std::cout << "Voce nao esta autenticado, autentica-se" << std::endl;
    }
}

void parser(Client& client){
    int i = 0;
    std::stringstream ss(client.buffer);
    std::string response;
    std::string cmd;
    
    while (std::getline(ss, response, ' ')){
        if (!response.empty()){
            if (i == 0){
                cmd = response;
                std::cout << "Command: " << response << std::endl;   
            }
            i++;
        }
    }
    cmd_start(client, cmd, i);
}