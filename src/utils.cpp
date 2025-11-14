/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:38:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/14 10:23:10 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.hpp"
#include <sstream>
#include <iomanip>

void send_irc_reply(Client& client_ref, std::string prefix, std::string command, std::string dest, const std::string& message){
    (void)client_ref;
    std::string toSend = ":" + prefix + " " + command + " " + dest + " :" + message + "\r\n";
    std::cout << toSend;
}

void send_irc_reply(Client& client_ref, std::string prefix, int code, std::string dest, const std::string& message){
    (void)client_ref;
    std::stringstream ss;

    ss << std::setw(3) << std::setfill('0') << code;
    std::string toSend = ":" + prefix + " " + ss.str() + " " + dest + " :" + message + "\r\n";
    std::cout << toSend;
}