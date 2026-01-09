/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:19:51 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:19:51 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.hpp"
#include <sstream>
#include <iomanip>
#include <map>
#include <fstream>
#include <sstream>

#include <sys/socket.h>

void send_irc_reply(Client& client_ref, std::string prefix, std::string command, std::string dest, const std::string& message){
    // (void)client_ref;
    std::string toSend = ":" + prefix + " " + command + " " + dest + " :" + message + "\r\n";
    send(client_ref.get_fd(), toSend.c_str(), toSend.length(), 0);
    std::cout << toSend;
}

void send_irc_reply(Client& client_ref, std::string prefix, int code, std::string dest, const std::string& message){
    // (void)client_ref;
    std::stringstream ss;

    ss << std::setw(3) << std::setfill('0') << code;
    std::string toSend = ":" + prefix + " " + ss.str() + " " + dest + " :" + message + "\r\n";
    send(client_ref.get_fd(), toSend.c_str(), toSend.length(), 0);
    std::cout << toSend;
}

bool isStringDigit(std::string str)
{
    int i = 0;
    while (i < (int)str.length())
    {
        if (!isdigit(str[i]))
        {
            return true;
        }
        i++;
    }
    return false;
}