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

void trim(std::string &str)
{
    // esquerda
    while (!str.empty() && std::isspace(str[0]))
        str.erase(0, 1);

    // direita
    while (!str.empty() && std::isspace(str[str.size() - 1]))
        str.erase(str.size() - 1, 1);
}

std::map<std::string, std::string> extract_conf(char **av)
{
    std::ifstream file(av[0]);
    std::string line;

    std::string data;
    std::string value;

    std::map<std::string, std::string> list_conf;
    if (!file.is_open())
    {
        throw std::runtime_error("Can't to open file: '.conf'");
    }
    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::getline(ss, data, '=');
        std::getline(ss, value, '=');
        trim(data);
        trim(value);
        if (data != "PASS" && data != "SERVERNAME" && data != "PORT")
        {
            throw std::runtime_error("Not enough parameter on .conf file");
        }
        list_conf[data] = value;
    }
    return (list_conf);
}