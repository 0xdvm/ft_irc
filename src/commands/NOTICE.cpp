/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:30:57 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/18 12:34:20 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/NOTICE.hpp"
#include "../../inc/utils.hpp"

NOTICE::NOTICE():Command(2){};

NOTICE::~NOTICE(){}

void NOTICE::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();

    if (size_args < 2)
        return;
    if (size_args >= 2)
    {
        if (args[0].at(0) != '#')
        {
            try
            {
                Client& client = server_ref.findUser(args[0]);
                
                send_irc_reply(client, client_ref.userMask(), "NOTICE", client.getNickname(), args[1]);
                //Nao faz nada!!!
                return;
            }
            catch(const std::exception& e){}
            return;   
        }
        else
        {
            try
            {
                
                Channel& channel = server_ref.findChannel(args[0]);
                if (!channel.isMember(target)) return;
                
                // std::cout << "O canal existe" << std::endl;
                channel.sendBroadcast("NOTICE", args[1], client_ref, false); 
            }
            catch(const std::exception& e){}
            return;    
        }
    }
}