/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:37:16 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:32:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/TOPIC.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"
#include <sys/socket.h>
#include <sstream>
#include <iomanip>
#include <ctime>

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
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, dest, "You're not on that channel");
                return;
            }

            if (!channel.hasTopic())
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_NOTOPIC, dest, "No topic is set");
                return;
            }
            else
            {                
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, dest, channel.getTopic());
                
                std::stringstream ss;
                ss << std::setw(3) << std::setfill('0') << RPL_TOPICWHOTIME;
                
                std::string toSend = ":" + server_ref.get_Servername() + " " + ss.str() + " " + target + " " + channel.getChannelName() + " " + channel.getTopicby() + " " + channel.getTopicTime() + "\r\n";
                send(client_ref.get_fd(), toSend.c_str(), toSend.size(), 0);
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
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, dest, "You're not on that channel");
                return;
            }

            if(!channel.isOperator(target) && channel.getTopicMode())
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, dest, "You're not a channel operator");
                // std::string dest =  channel.getChannelName() + " " + target;     
                // //:<servername> <code>  <channel> <nick> <:message>          
                // send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, dest, "You're not a channel operator");
                return;
            }
            std::string topic;
            if (args[1].at(0) == ':')
            {
                topic = args[1].substr(1);
            }
            else
            {
                topic = args[1];
            }
            channel.setTopic(topic);
            channel.setTopicby(client_ref.userMask());
            
            time_t now = time(NULL);
            long int now_int = (long int)now;
            
            channel.setTopicTime(now_int);
            std::string tosend = channel.getTopic();

            channel.sendBroadcast("TOPIC", tosend, client_ref,true);
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
        }
        
    }
}