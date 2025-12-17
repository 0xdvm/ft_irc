/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:19:34 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/17 19:49:48 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/MODE.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"
#include <cstring>
#include <map>

MODE::MODE(): Command(3){}

MODE::~MODE(){}

void MODE::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args){
    int size_args = args.size();
    std::string target = "*";

    if (client_ref.hasNick()){
        target = client_ref.getNickname();
    }
    if (size_args < 2){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
    if (size_args >= 1 && args[0].at(0) == '#'){
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);
            if (!channel.isMember(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target + " " + channel.getChannelName(), "You're not on that channel");
                return;
            }
            if (!channel.isOperator(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target + " " + channel.getChannelName(), "You're not operator");
                return;
            }
            
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return;
        }
    }
    if((strchr("itkol", args[1].at(1)) == NULL) || args[1].size() != 2){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_UNKNOWNMODE, target, "is unknown mode char to me");
        return;
    }
    
    std::cout << "Tudo correto" << std::endl;
}
