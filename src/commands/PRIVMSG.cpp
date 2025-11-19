/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:47:27 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/19 16:17:39 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/PRIVMSG.hpp"
#include "../../inc/utils.hpp"

PRIVMSG::PRIVMSG(): Command(2){}

PRIVMSG::~PRIVMSG(){}

void PRIVMSG::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args){
    int size_args = args.size();
    
    if (size_args != this->get_num_args()){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, client_ref.getNickname(), "Not enough parameters");
        return;
    }
    if (args[0] != "#"){
        
        try{
            Client& client = server_ref.findUser(args[0]);

            if (!client.isAuthenticated()){
                return;
            }
            std::string target = client.getNickname();
            std::string message = args[1];
            std::string emissor = client_ref.getNickname()
            + "!" + client_ref.getUsername() + "@" + client_ref.getServername();
            
            send_irc_reply(client, emissor, "PRIVMSG", target, message);
        }
        catch(const std::exception& e){
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, args[0], "No such nick");
        }
        return;
    }
    std::cout << "Estou aqui, nao se preocupe" << std::endl;
    
}
