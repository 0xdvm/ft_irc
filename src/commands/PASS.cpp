/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:19:54 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/12 21:04:29 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/PASS.hpp"
#include <unistd.h>

PASS::PASS(): Command(1){}

PASS::~PASS(){}

void PASS::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args) const{
    int num_args = args.size();
    
    if (client_ref.hasPass()){
        std::cout << ":ircserv 500 PASS : You have already sent the password!!" << std::endl;
        return;
    }
    
    if (num_args > this->get_num_args()){
        std::cout << ":ircserv 417 PASS :invalid argument" << std::endl;
        return;
    }

    if (args.at(0).compare(server_ref.get_password()) != 0){
        std::cout << ":ircserv 450 PASS :invalid password" << std::endl;
        
        std::cout << ":ircserv 407 :You will be desconnected from irc.serv" << std::endl;
        std::cout << "size: " << args.at(0).compare(server_ref.get_password()) << std::endl;
        //Desconectando o cliente do servidor.
        close(client_ref.get_fd());
        return;
    }
    client_ref.setPass(true);
}