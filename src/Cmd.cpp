/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cmd.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:52:08 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/11 06:48:40 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Cmd.hpp"
#include <sstream>

Cmd::Cmd(){}

Cmd::Cmd(std::string password){
    this->password = password;    
}

Cmd::~Cmd(){}

Cmd& Cmd::operator=(const Cmd& other){
    if (this != &other){
        this->password = other.password;
    }
    return (*this);
}

void Cmd::cmd_start(Client& client, std::string cmd, int size_args){
    (void)size_args;
    (void)cmd;
    
    if (cmd == "CAP" && !client.isAuthenticated()){
        std::cout << ":irc.server: CAP * LS :" << std::endl;
    }
    else{
        std::cout << "Voce nao esta autenticado, autentica-se" << std::endl;
    }
}

void Cmd::parser(Client& client){
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