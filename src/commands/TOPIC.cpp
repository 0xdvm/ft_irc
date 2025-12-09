/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 18:37:16 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/09 11:57:38 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/TOPIC.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"
#include <sys/socket.h>
#include <sstream>
#include <iomanip>

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
                // std::string send = RPL_TOPIC + " " + target + " " + channel.getChannelName() + " :" + channel.getTopic() + "\r\n";
                // std::string toSend = RPL_TOPIC + " " + target + " " + channel.getChannelName() + " :" + channel.getTopic() + "\r\n";
                
                
                // :server 332 <nick> <canal> :<tópico atual>
                // :server 333 <nick> <canal> <set_by> <timestamp>
                
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPIC, dest, channel.getTopic());
                
                std::stringstream ss;
                ss << std::setw(3) << std::setfill('0') << RPL_TOPICWHOTIME;
                
                std::string toSend = ":" + server_ref.get_Servername() + " " + ss.str() + " " + target + " " + channel.getChannelName() + " " + channel.getTopicby() + " " + channel.getTopicTime() + "\r\n";
                send(client_ref.get_fd(), toSend.c_str(), toSend.size(), 0);
                
                // send_irc_reply(client_ref, server_ref.get_Servername(), RPL_TOPICWHOTIME,  )
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
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, target + " " + channel.getChannelName(),"You're not a channel operator");
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
            channel.setTopicby(client_ref.userMask());
            
            channel.setTopicTime(125289382);
            std::string tosend = channel.getTopic();

            channel.sendBroadcast("TOPIC", tosend, client_ref);
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");
        }
        
    }
}