/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:37:16 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/01 09:34:10 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/TOPIC.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"

TOPIC::TOPIC():Command(2){}

TOPIC::~TOPIC(){}

void TOPIC::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();

    if (size_args == 0)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
    if (size_args == 1)
    {
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);  
            
            if (!channel.isMember(target))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target, "You're not on that channel");
                return;
            }
            if (channel.hasTopic())
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_NOTOPIC, target, "No topic is set");
                return;
            }
            else
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, target, channel.getTopic());
                return;
            }
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
            return;
        }
        return;
    }
    else
    {
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);

            if (!channel.isMember(target))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target, "You're not on that channel");
                return;
            }

            if(!channel.isOperator(target))
            {
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, target,"You're not a channel operator");
                return;
            }
            std::string topic;
            if (args[1].at(0) == ':')
            {
                topic = args[1].substr(1);
                std::cout << "STRING: " << topic << std::endl;
            }
            else
            {
                topic = args[1];
            }
            channel.setTopic(topic);
            std::string tosend = channel.getTopic();

            channel.sendBroadcast("TOPIC", tosend, client_ref);
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
        }
        
    }
}