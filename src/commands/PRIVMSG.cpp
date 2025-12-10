/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:47:27 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/09 12:54:07 by dvemba           ###   ########.fr       */
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
    if (args[0].at(0) != '#'){
        
        try
        {
            Client& client = server_ref.findUser(args[0]);

            if (!client.isAuthenticated())
            {
                return;
            }
            std::string target = client.getNickname();
            std::string message = args[1];
            std::string emissor = client_ref.userMask();
            
            send_irc_reply(client, emissor, "PRIVMSG", target, message);
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, args[0], "No such nick");
        }
    }
    else
    {
        try
        {
            Channel channel = server_ref.findChannel(args[0]);
            if (!channel.isMember(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CANNOTSENDTOCHAN, client_ref.getNickname() + " " + channel.getChannelName(), "Cannot send to channel");
                return;
            }
            channel.sendBroadcast("PRIVMSG", args[1], client_ref, false);
            
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, args[0], "No such channel");
        }
    }
    // std::cout << "Estou aqui, nao se preocupe" << std::endl;
    
}
