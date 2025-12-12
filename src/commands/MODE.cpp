/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:19:34 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/12 21:01:01 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/MODE.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"
#include <stdexcept>

MODE::MODE(): Command(3){}

MODE::~MODE(){}

bool isValidMode(char flag)
{
    if (flag != 't' && flag != 'o' && flag != 'i' && flag != 'k' && flag != 'l')
        return (false);
    return (true);
}

bool isValidOperator(char c)
{
    if (c != '+' && c != '-')
        return (false);
    return (true);
}
bool isModeParam(std::string modes)
{
    if (modes != "+o" && modes != "-o" && modes != "+k" && modes != "+l")
        return (false);
    return (true);
}
void MODE::validateModes(std::vector<std::string> args)
{
    std::vector<std::string>::iterator it = args.begin() + 1;
    std::string modes;
    
    while (it != args.end())
    {
        std::string str = (*it);
        if (!isValidOperator(str[0]))
        {
            this->arguments_modes.push_back(str);
        }
        else
        {
            for (int i = 1; i < static_cast<int>(str.size()); i++)
            {
                if (!isValidMode(str[i]))
                {
                    modes.clear();
                    modes.push_back(str[i]);
                    throw std::runtime_error(modes);
                }
                if (str[0] == '+')
                {
                    modes.clear();
                    modes.push_back('+');
                    modes.push_back(str[i]);
                    this->list_modes.push_back(modes);
                }
                else
                {
                    modes.clear();
                    modes.push_back('-');
                    modes.push_back(str[i]);
                    this->list_modes.push_back(modes);
                }
            }
        }
        it++;
    }
}
void MODE::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args){
    int size_args = args.size();
    std::string target = "*";
    
    if (client_ref.hasNick()){target = client_ref.getNickname();}
    if (size_args == 0){
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
        return;
    }
    if (size_args == 1)
    {
        if (args[0].at(0) != '#')
        {
            try
            {
                Client& client = server_ref.findUser(args[0]);
                if (client.getNickname().compare(target) != 0)
                {
                    send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHSERVER, target, "Can't change mode for other users");
                    return;
                }
                //Nao faz nada!!!
                return;
            }
            catch(const std::exception& e){send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, target, "No such nick");}
            return;   
        }
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);
            
            if (!channel.isMember(target))
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, dest, "You're not on that channel");
                return;
            }
            //mostra os modos ativos no canal corrente
            //
        }
        catch(const std::exception& e){send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");}
        return;
    }
    if (size_args > 1)
    {
        if (args[0].at(0) != '#')
        {
            try
            {
                Client& client = server_ref.findUser(args[0]);
                if (client.getNickname().compare(target) != 0)
                {
                    send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHSERVER, target, "Can't change mode for other users");
                    return;
                }
                //Nao faz nada!!!
                return;
            }
            catch(const std::exception& e){send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHNICK, target, "No such nick");}
            return;   
        }
        try
        {
            Channel& channel = server_ref.findChannel(args[0]);
            
            if (!channel.isMember(target))
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, dest, "You're not on that channel");
                return;
            }
            if (!channel.isOperator(target))
            {
                std::string dest = target + " " + channel.getChannelName();
                send_irc_reply(client_ref, server_ref.get_Servername(), ERR_CHANOPRIVSNEEDED, dest, "You're not a channel operator");
                return;
            }
            //modifica o canal com os modos adicionados...
            //
            try{validateModes(args);}
            catch(const std::exception& e){send_irc_reply(client_ref, server_ref.get_Servername(), ERR_UNKNOWNMODE, target, e.what()); return;}
            //
            {
                int count_mode_params = 0;
                for (int i = 0; i < static_cast<int>(this->list_modes.size()); i++)
                {
                    if (isModeParam(this->list_modes[i]))
                        count_mode_params++;
                }
                if (static_cast<int>(arguments_modes.size()) < count_mode_params)
                {
                    send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NEEDMOREPARAMS, target, "Not enough parameters");
                    return;           
                }
            }
            // {
            //     for (int i = 0; i < static_cast<int>(list_modes.size()); i++)
            //     {
                    
            //     }
            // }
        }
        catch(const std::exception& e){send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target, "No such channel");}
        return;
    }
    
}
