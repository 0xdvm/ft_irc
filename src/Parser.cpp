/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:52:08 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/11 06:48:40 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Parser.hpp"
#include <sstream>

Parser::Parser(){}

Parser::Parser(Client& client_ref, std::string password): password(password){
    int i = 0;
    std::stringstream ss(client_ref.buffer);
    std::string response;
    std::string cmd;
    
    while (std::getline(ss, response, ' ')){
        if (!response.empty()){
            if (i == 0){
                cmd = response;
                std::cout << "Command: " << response << std::endl;   
            }
            i++;
        }
    }
    this->Parser_start(client_ref, cmd, i);
}

Parser::~Parser(){}

Parser& Parser::operator=(const Parser& other){
    if (this != &other){
        this->password = other.password;
    }
    return (*this);
}

void Parser::Parser_start(Client& client_ref, std::string cmd, int size_args){
    (void)size_args;
    (void)cmd;
    (void)client_ref;
}
