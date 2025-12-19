/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:20:15 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:20:15 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/PING.hpp"
#include "../../inc/utils.hpp"
#include "sys/socket.h"

PING::PING():Command(1){}

PING::~PING(){}

void PING::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = "*";
    
    if (client_ref.hasNick())
    {
        target = client_ref.getNickname();
    }
    if (size_args == 0)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
    std::string reply = "PONG " + args[0] + "\r\n";
    // std::cout << reply << std::endl;
    // send(client_ref.get_fd(), reply.c_str(), reply.size(), 0);
    send_irc_reply(client_ref, server_ref.get_Servername(), "PONG", server_ref.get_Servername(), args[0]);
}