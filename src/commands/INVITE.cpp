/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:39:05 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/17 20:39:11 by cgouveia         ###   ########.fr       */
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
    if (size_args >= 2 && args[1].at(0) != '#')
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
        return;
    }
    if (size_args >= 2)
    {   
        try
        {
            Channel& channel = server_ref.findChannel(args[1]);
             std::cout << "Ja existe este canal" << std::endl;
            if (!channel.isMember(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target + " " + channel.getChannelName(), "You're not on that channel");
                return;
            }
            std::cout << "Verificando se o modo i esta ativo" << std::endl;
            if (channel.getInviteMode() == true && !channel.isOperator(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, target + " " + channel.getChannelName(), "You're not channel operator");
                return;
            }
            std::cout << "Verificando se o nick existe" << std::endl;
            if (server_ref.findClient(args[0]).getNickname().empty())
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, target + " " + args[0], "No such nick");
                return;
            }
            std::cout << "Verificando se ja e membro do canal" << std::endl;
            if (channel.isMember(args[0]))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_USERNOTINCHANNEL, target + " " + channel.getChannelName(), "The user is not on this channel.");
                return;
            }
            channel.setInvite(client_ref.getNickname(), args[0], server_ref);
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
