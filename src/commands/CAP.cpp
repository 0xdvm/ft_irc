/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:26:26 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:31:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/CAP.hpp"
#include "../../inc/utils.hpp"

CAP::CAP(): Command(1){}

void CAP::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
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
    if (args[0].compare("LS") != 0 && args[0].compare("ACK") != 0 && args[0].compare("REQ") != 0)
    {
        return;
    }
    send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Capabilities not supported");
}