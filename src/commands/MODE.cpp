/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:19:34 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/17 19:49:48 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/MODE.hpp"
#include "../../inc/utils.hpp"

MODE::MODE(): Command(3){}

MODE::~MODE(){}

void MODE::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args){
    int size_args = args.size();
    std::string target = "*";
    
    if (client_ref.hasNick()){
        target = client_ref.getNickname();
    }
    if (size_args < 2){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
}
