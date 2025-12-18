/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:42:36 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/17 20:42:42 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/KICK.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"

KICK::KICK(): Command(2) {}

KICK::~KICK(){}

void KICK::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();
    
    if (size_args < 2)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough paramters");
        return;
    }
    if (size_args >= 2 && args[0].at(0) != '#')
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
        return;
    }
    if (size_args >= 2)
    {   
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
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, target + " " + channel.getChannelName(), "You're not channel operator");
                return;
            }
            if (server_ref.findClient(args[1]).getNickname().empty())
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, target + " " + args[0], "No such nick");
                return;
            }
            if (!channel.isMember(args[1]))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_USERNOTINCHANNEL, target + " " + channel.getChannelName(), "The user is not on this channel.");
                return;
            }
            std::string tosend = "has left " + channel.getChannelName();
            // send_irc_reply(client_ref, client_ref.userMask(), "PART", channel.getChannelName(), tosend);
            Client &target = server_ref.findClient(args[1]);
            std::string reason = (size_args >= 3 && !args[2].empty())? args[2] : "kicked";
            channel.sendBroadcastKick(client_ref, target, reason);
            channel.removeMember(args[1]);
            channel.removeInviteList(args[1]);
        }
        catch(const std::exception& e)
        {            
            //Channel& channel =  server_ref.findChannel(args[1]);
            std::cout << "Nao existe este canal : " << args[1] << std::endl;
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return; 
        }
    }
}
