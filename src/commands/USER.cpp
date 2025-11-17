/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:22:27 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/17 10:38:00 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/USER.hpp"
#include "../../inc/utils.hpp"

USER::USER(): Command(4){}

USER::~USER(){}

bool USER::isValidUsername(std::string& username){
    int i = 0;

    while (username[i]){
        if (username[i] != '_' && username[i] != '-' && !isdigit(username[i]) 
            && !((username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= 'a' && username[i] <= 'z'))){
                return (false);
        }
        i++;
    }
    return (true);
}

bool USER::isValidRealname(std::string& realname){
    int i = 0;

    while (realname[i]){
        if ((realname[i] >= 'A' && realname[i] <= 'Z') || (realname[i] >= 'a' && realname[i] <= 'z')){
            return (true);
        }
        i++;
    }
    return (false);
}

void USER::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args){
    int size_args = args.size();
    std::string target = "*";
    
    if (client_ref.hasNick()){
        target = client_ref.getNickname();
    }
    if (size_args < this->get_num_args()){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
    if (!client_ref.hasPass() || !client_ref.hasNick()){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTREGISTERED, "USER", "You have not registered");
        return;
    }
    if (!this->isValidUsername(args[0])){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_PASSWDMISMATCH, args[0], "Invalid username");
        return;
    }
    if (args[3].at(0) != ':' || !this->isValidRealname(args[3])){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_PASSWDMISMATCH, args[3], "Invalid realname");
        return;
    }
    if (client_ref.hasUser()){
        target = client_ref.getNickname();
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_ALREADYREGISTERED, target, "You may not reregister");
        return;
    }
    
    client_ref.setUsername(args[0]);
    client_ref.setHost(args[1]);
    client_ref.setServername(args[2]);
    
    //Removendo o ':'
    args[3] = args[3].substr(1);
    client_ref.setRealname(args[3]);
    
    client_ref.setUser(true);
    client_ref.setAuthenticated(true);

    send_irc_reply(client_ref, server_ref.get_Servername(), RPL_WELCOME, target, "Welcome to the IRCSERV");
    send_irc_reply(client_ref, server_ref.get_Servername(), RPL_YOURHOST, target, "Your host is server, running version 1.0");
    send_irc_reply(client_ref, server_ref.get_Servername(), RPL_CREATED, target, "This server was created on 2025-11-17");
}