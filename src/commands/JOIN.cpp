/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:32:04 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/09 12:33:03 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/JOIN.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"

JOIN::JOIN(): Command(2) {}

JOIN::~JOIN(){}

void JOIN::showInfo()
{
    
}

void JOIN::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
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
        send_irc_reply(client_ref, server_ref.get_password(), ERR_NOSUCHCHANNEL, target, "No such channel");
        return;
    }
    if (size_args == 1)
    {   
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);
            // std::cout << "Ja existe este canal" << std::endl;
            if (channel.hasPassword())
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_BADCHANNELKEY, target + " " + channel.getChannelName(), "Cannot join channel (+k) - bad key");
                return;
            }
            if (channel.isMember(client_ref.getNickname()))
            {
                return;
            } 
            channel.joinChannel(client_ref);
            if (channel.hasTopic())
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, target + " " + channel.getChannelName(), channel.getTopic());
            else
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, target + " " + channel.getChannelName(), "");
            send_irc_reply(client_ref, server_ref.get_Servername(), RPL_NAMREPLY, target + " = " + channel.getChannelName(), channel.getListmember());
            send_irc_reply(client_ref, server_ref.get_password(), RPL_ENDOFNAMES, target + " " + channel.getChannelName(), "End of NAMES list");
        }
        catch(const std::exception& e)
        {            
            Channel& channel =  server_ref.createChannel(args[0], "");
            // std::cout << "Nao existe este canal" << std::endl;
            if (channel.hasPassword())
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_BADCHANNELKEY, target + " " + channel.getChannelName(), "Cannot join channel (+k) - bad key");
                return;
            }
            if (channel.isMember(client_ref.getNickname()))
            {
                return;
            } 
            channel.joinChannel(client_ref);
            if (channel.hasTopic())
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, target + " " + channel.getChannelName(), channel.getTopic());
            else
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, target + " " + channel.getChannelName(), "");
            
            send_irc_reply(client_ref, server_ref.get_Servername(), RPL_NAMREPLY, target + " = " + channel.getChannelName(), channel.getListmember());
            send_irc_reply(client_ref, server_ref.get_password(), RPL_ENDOFNAMES, target + " " + channel.getChannelName(), "End of NAMES list");
        }
    }
    else
    {
        try
        {
            Channel &channel = server_ref.findChannel(args[0]);
            if (!channel.isCorrectpassword(args[1]))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_BADCHANNELKEY, target + " " + channel.getChannelName(), "Cannot join channel (+k) - bad key");
                return;
            }
            if (channel.isMember(client_ref.getNickname()))
            {
                return;
            } 
            channel.joinChannel(client_ref);
            
        }
        catch(const std::exception& e)
        {            
            Channel &channel =  server_ref.createChannel(args[0], args[1]);

            if (channel.isMember(client_ref.getNickname()))
            {
                return;
            } 
            channel.joinChannel(client_ref);
        }
    }
}