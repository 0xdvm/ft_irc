/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:19:54 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:32:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/PASS.hpp"
#include <unistd.h>
#include "../../inc/utils.hpp"

PASS::PASS(): Command(1){}

PASS::~PASS(){}

void PASS::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int num_args = args.size();
    std::string target = "*";
    
    if (client_ref.hasNick())
    {
        target = client_ref.getNickname();
    }
    if (num_args == 0)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
    
    if (client_ref.hasPass())
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_ALREADYREGISTERED, target, "You may not reregister");
        return;
    }
    
    if (args.at(0).compare(server_ref.get_password()) != 0)
    {
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_PASSWDMISMATCH, target, "Password incorrect");
        //Desconectando o cliente do servidor.
        close(client_ref.get_fd());
        return;
    }
    client_ref.setPass(true);
}