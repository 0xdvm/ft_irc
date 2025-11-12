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
#include <vector>

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
    this->Parser_start(client_ref, cmd);
}

Parser::~Parser(){}

Parser& Parser::operator=(const Parser& other){
    if (this != &other){
        this->password = other.password;
    }
    return (*this);
}

void Parser::Parser_start(Client& client_ref, std::string cmd){
    std::vector<std::string> args;
    std::stringstream ss(client_ref.buffer);
    std::string argument;
    
    while(std::getline(ss, argument, ' ')){
        if (!argument.empty()){
            if (argument.compare(cmd) != 0){
                if (argument.at(0) == ':' && argument.size() > 1){
                    int pos = ss.str().find(':');
                    pos++;

                    argument = ss.str().substr(pos);

                    //Remove o '\n' no final da string.
                    if (argument[argument.size() - 1] == '\n'){
                        argument[argument.size() - 1] = '\0';
                    }
                    args.push_back(argument);
                    break;
                }
                //Remove o '\n' no final da string.
                if (argument[argument.size() - 1] == '\n'){
                    argument[argument.size() - 1] = '\0';
                }
                args.push_back(argument);
            }
        }
    }

    std::vector<std::string>::iterator it = args.begin();
    while (it != args.end()){
        std::cout << *it << std::endl;
        it++;
    }
    std::cout << "Size: " << args.size() << std::endl;
    
}
