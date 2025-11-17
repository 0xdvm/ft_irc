/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:38:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/17 10:49:35 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.hpp"
#include <sstream>
#include <iomanip>
#include <sys/socket.h>

void send_irc_reply(Client& client_ref, std::string prefix, std::string command, std::string dest, const std::string& message){
    (void)client_ref;
    std::string toSend = ":" + prefix + " " + command + " " + dest + " :" + message + "\r\n";
    send(client_ref.get_fd(), toSend.c_str(), toSend.length(), 0);
    std::cout << toSend;
}

void send_irc_reply(Client& client_ref, std::string prefix, int code, std::string dest, const std::string& message){
    (void)client_ref;
    std::stringstream ss;

    ss << std::setw(3) << std::setfill('0') << code;
    std::string toSend = ":" + prefix + " " + ss.str() + " " + dest + " :" + message + "\r\n";
    send(client_ref.get_fd(), toSend.c_str(), toSend.length(), 0);
    std::cout << toSend;
}


// void send_irc_reply(Client& client_ref, std::string prefix, std::string command, std::string dest, const std::string& message){
//     (void)client_ref;
//     std::string toSend = "\033[1;35m:" + prefix + "\033[0m \033[32m" + command + "\033[0m " + dest + " \033[34m:" + message + "\033[0m\r\n";

//     send(client_ref.get_fd(), toSend.c_str(), toSend.length(), 0);
//     std::cout << toSend;
// }

// void send_irc_reply(Client& client_ref, std::string prefix, int code, std::string dest, const std::string& message){
//     (void)client_ref;
//     std::stringstream ss;

//     ss << std::setw(3) << std::setfill('0') << code;
//     std::string toSend = "\033[1;35m:" + prefix + "\033[0m \033[32m" + ss.str() + "\033[0m " + dest + " \033[34m:" + message + "\033[0m\r\n";
    
//     send(client_ref.get_fd(), toSend.c_str(), toSend.length(), 0);
//     std::cout << toSend;
// }