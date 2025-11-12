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

#include "../inc/commands/PASS.hpp"

Parser::Parser(const Server& server_ref, Client& client_ref){
    //Incializa a lista de commandos...
    this->list_commands = get_list_commands();

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
    //Incia o parsing do commandos...
    this->Parser_start(server_ref, client_ref, cmd);
}

Parser::~Parser(){
    std::map<std::string, Command *>::iterator it;
    for (it = this->list_commands.begin(); it != this->list_commands.end(); it++){
        delete it->second;
    }
    this->list_commands.clear();
}

std::map<std::string, Command *> Parser::get_list_commands(){
    std::map<std::string, Command*> commads;

    commads["PASS"] = new PASS();
    return (commads);
}

void Parser::Parser_start(const Server& server_ref, Client& client_ref, std::string cmd){

    std::vector<std::string> args;
    std::stringstream ss(client_ref.buffer);
    std::string argument;
    
    //Listando os argumentos...
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
    //Verificando se o comando existe.
    if (this->list_commands[cmd]){
        std::vector<std::string>::iterator it = args.begin();
        while (it != args.end()){
            std::cout << *it << std::endl;
            it++;
        }
        std::cout << "Size: " << args.size() << std::endl;
        this->list_commands[cmd]->run_command(server_ref, client_ref, args);
    }
    else{
        std::cout << ":ircserv 417 " << cmd << ": invalid command" << std::endl;
    }
}
