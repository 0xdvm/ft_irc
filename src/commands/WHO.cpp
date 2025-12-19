/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHO.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:14:32 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 16:43:00 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/WHO.hpp"
#include "../../inc/utils.hpp"

WHO::WHO(): Command(1){}

WHO::~WHO(){}

void WHO::who_channel(Server &server_ref, Client& client_ref, Channel channel)
{
    std::map<std::string, Client> list = channel.getMember();
    std::map<std::string, Client>::iterator it = list.begin();
    
    while (it != list.end())
    {
        // <canal> <username> <host> <server> <nick> <flags>
        std::string dest;
        dest.append(client_ref.getNickname());
        dest.append(" " + channel.getChannelName());
        dest.append(" " + (it->second).getUsername());
        dest.append(" " + (it->second).getHost());
        dest.append(" " + server_ref.get_Servername());
        dest.append(" " + (it->second).getNickname());
        if (channel.isOperator((it->second).getNickname()))
            dest.append(" H@");
        else
            dest.append(" H");
        send_irc_reply(client_ref, server_ref.get_Servername(), RPL_WHOREPLY, dest, "0 " + (it->second).getRealname());
        it++;
    }

    
}
void WHO::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();

    if (size_args  < 1)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not engouh parameters");
        return;
    }
    if (size_args >= 1)
    {
        if (args[0].at(0) == '#')
        {
            try
            {
                Channel& channel = server_ref.findChannel(args[0]);
                
                if (channel.isMember(target)){who_channel(server_ref, client_ref, channel);}
            }
            catch(const std::exception& e){}
        }
        else
        {
            try
            {
                Client& client = server_ref.findUser(args[0]);

                std::string dest;
                dest.append(client_ref.getNickname());
                dest.append(" *");
                dest.append(" " + (client).getUsername());
                dest.append(" " + (client).getHost());
                dest.append(" " + server_ref.get_Servername());
                dest.append(" " + (client).getNickname());
                dest.append(" H");
                send_irc_reply(client_ref, server_ref.get_Servername(), RPL_WHOREPLY, dest, "0 " + client.getRealname());
            }
            catch(const std::exception& e){}
        }
        std::string dest = target + " " + args[0];
        send_irc_reply(client_ref, server_ref.get_Servername(), RPL_ENDOFWHO, dest, "End of /WHO list");
    }
}