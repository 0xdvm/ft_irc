/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:05:43 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/09 19:05:47 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/QUIT.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"
#include <unistd.h>

QUIT::QUIT(): Command(2){}

QUIT::~QUIT(){}

void QUIT::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();

    if (size_args == 0 || size_args > 1)
    {
        try
        {
            std::list<Channel *>::iterator it = server_ref.getListChannel().begin();
            while (it != server_ref.getListChannel().end())
            {
                int i = 0;
                Channel* channel = *it;

                if (channel->isMember(client_ref.getNickname()))
                {
                    std::string tosend = "has quit ";
                    // send_irc_reply(client_ref, client_ref.userMask(), "QUIT", channel.getChannelName(), tosend);
                    channel->sendBroadcastQuit("QUIT", "Client quit", client_ref, true);
                    channel->removeMember(client_ref.getNickname());
                    if (channel->getListmember().empty())
                    {
                        i = 1;
                        it++;
                        server_ref.removeChannel(channel->getChannelName());
                    }
                }
                if (i == 0)
                    it++;
            }
            close(client_ref.get_fd());
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return;
        }
    }

    if (size_args == 1)
    {
        try
        {
            std::list<Channel *>::iterator it = server_ref.getListChannel().begin();
            while (it != server_ref.getListChannel().end())
            {
                int i = 0;
                Channel* channel = *it;

                if (channel->isMember(client_ref.getNickname()))
                {
                    std::string tosend = "has quit " + channel->getChannelName();
                    // send_irc_reply(client_ref, client_ref.userMask(), "QUIT", channel.getChannelName(), tosend);
                    channel->sendBroadcastQuit("QUIT", args[0], client_ref, true);
                    channel->removeMember(client_ref.getNickname());
                    if (channel->getListmember().empty())
                    {
                        i = 1;
                        it++;
                        server_ref.removeChannel(channel->getChannelName());
                    }
                }
                if (i == 0)
                    it++;
            }
            close(client_ref.get_fd());
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return;
        }
    }
}
