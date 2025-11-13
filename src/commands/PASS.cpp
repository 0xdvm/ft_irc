/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:19:54 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/13 21:01:44 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/PASS.hpp"
#include <unistd.h>
#include "../../inc/utils.hpp"

PASS::PASS(): Command(1){}

PASS::~PASS(){}

void PASS::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args) const{
    int num_args = args.size();
    
    if (client_ref.hasPass()){
        send_irc_reply("ircserv", "500", "*", "You may not reregister");
        return;
    }
    
    if (num_args > this->get_num_args()){
        send_irc_reply("ircserv", "417", "*", "Not enough parameters");
        return;
    }

    if (args.at(0).compare(server_ref.get_password()) != 0){
        send_irc_reply("ircserv", "450", "*", "Password incorrect");
        send_irc_reply("ircserv", "407", "*", "You will be desconnected from irc.serv");
        //Desconectando o cliente do servidor.
        close(client_ref.get_fd());
        return;
    }
    client_ref.setPass(true);
}