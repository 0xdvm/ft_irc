/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:21:16 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/14 21:04:17 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/NICK.hpp"
#include "../../inc/utils.hpp"

NICK::NICK(): Command(1){}

NICK::~NICK(){}

bool NICK::isvalidNickname(std::string nickname){
    int i = 0;

    while (nickname[i]){
        if ((nickname[i] >= 'a' && nickname[i] <= 'z') || (nickname[i] >= 'A' && nickname[i] <= 'Z')){
            break;
        }
        i++;
    }
    if (i != 0){
        return (false);
    }
    return (true);
}

bool NICK::isFreeNick(Server& server_ref, std::string nickname){
    
    std::map<int, Client> clients = server_ref.getListClient();
    std::map<int, Client>::iterator it = clients.begin();
    while (it != clients.end())
    {
        if (it->second.getNickname() == nickname){
            return (false);
        }
        it++;
    }
    return (true);
}

void NICK::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args) {
    int size_args = args.size();
    std::string target = "*";

    if (size_args == 0){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NONICKNAMEGIVEN, target, "No nickname given");
        return;
    }
    if (!client_ref.hasPass()){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTREGISTERED, "NICK", "You have not registered");
        return;
    }
    if (!this->isvalidNickname(args[0])){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_ERRONEUSNICKNAME, args[0], "Erroneus nickname");
        return;
    }
    if(!this->isFreeNick(server_ref, args[0])){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NICKNAMEINUSE, args[0], "Nickname is already in use");
        return;
    }
    if (client_ref.hasNick()){
        return;
    }
    client_ref.setNickname(args[0]);
    client_ref.setNick(true);
}