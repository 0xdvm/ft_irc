/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:05:29 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/09 19:05:34 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/PART.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"

PART::PART(): Command(2){}

PART::~PART(){}

void PART::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();

    if (size_args == 0)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough paramters");
        return;
    }
    if (size_args >= 1 && args[0].at(0) != '#')
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
        return;
    }

    if (size_args == 1)
    {
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);
            if (!channel.isMember(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target + " " + channel.getChannelName(), "You're not on that channel");
                return;
            }
            std::string tosend = "has left " + channel.getChannelName();
            // send_irc_reply(client_ref, client_ref.userMask(), "PART", channel.getChannelName(), tosend);
            channel.sendBroadcast("PART", "", client_ref, true);
            channel.removeMember(client_ref.getNickname());
            if (channel.getListmember().empty())
            {
                server_ref.removeChannel(channel.getChannelName());
            }
            
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return;
        }
    }

    if (size_args > 1)
    {
        std::cout << args[1].at(0) << std::endl;
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);
            if (!channel.isMember(client_ref.getNickname()))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target + " " + channel.getChannelName(), "You're not on that channel");
                return;
            }
            std::string tosend = "has left " + channel.getChannelName();
            // send_irc_reply(client_ref, client_ref.userMask(), "PART", channel.getChannelName(), tosend);
            channel.sendBroadcast("PART", args[1], client_ref, true);
            channel.removeMember(client_ref.getNickname());
            if (channel.getListmember().empty())
            {
                server_ref.removeChannel(channel.getChannelName());
            }
            
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return;
        }
    }
    
    
    
}
