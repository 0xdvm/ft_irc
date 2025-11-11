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

Parser::Parser(Client& client, std::string password): password(password){
    int i = 0;
    std::stringstream ss(client.buffer);
    std::string response;
    std::string Parser;
    
    while (std::getline(ss, response, ' ')){
        if (!response.empty()){
            if (i == 0){
                Parser = response;
                std::cout << "Command: " << response << std::endl;   
            }
            i++;
        }
    }
    this->Parser_start(client, Parser, i);
}

Parser::~Parser(){}

Parser& Parser::operator=(const Parser& other){
    if (this != &other){
        this->password = other.password;
    }
    return (*this);
}

void Parser::Parser_start(Client& client, std::string Parser, int size_args){
    (void)size_args;
    (void)Parser;
    
    if (Parser == "CAP" && !client.isAuthenticated()){
        std::cout << ":irc.server: CAP * LS :" << std::endl;
    }
    else{
        std::cout << "Voce nao esta autenticado, autentica-se" << std::endl;
    }
}
