/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:38:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/13 21:27:17 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/utils.hpp"

void send_irc_reply(Client& client_ref, std::string prefix, std::string command, std::string dest, const std::string& message){
    (void)client_ref;
    std::string toSend = ":" + prefix + " " + command + " " + dest + " :" + message + "\r\n";
    std::cout << toSend;
}