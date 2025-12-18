/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:01:23 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 17:01:23 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/INVITE.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"

INVITE::INVITE(): Command(2) {}

INVITE::~INVITE(){}

void INVITE::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();
    
    if (size_args < 2)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough paramters");
        return;
    }
    if (size_args >= 2)
    {   
        try
        {
            Channel& channel = server_ref.findChannel(args[1]);
            //  std::cout << "Ja existe este canal" << std::endl;
            if (!channel.isMember(target))
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target, "You're not on that channel");
                return;
            }
            // std::cout << "Verificando se o modo i esta ativo" << std::endl;
            if (channel.getInviteMode() && !channel.isOperator(target))
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, dest, "You're not a channel operator");
                return;
            }

            try
            {
                Client &client = server_ref.findClient(args[0]);

                if (channel.isMember(args[0])){return;}

                channel.setInvite(client, client_ref);

            }
            catch(const std::exception& e){send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, target, "No such nick");}
            
        }
        catch(const std::exception& e)
        {            
            //Channel& channel =  server_ref.findChannel(args[1]);
            std::cout << "Nao existe este canal : " << args[1] << std::endl;
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[1], "No such channel");
            return; 
        }
    }
}
