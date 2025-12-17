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

#include "../inc/utils.hpp"
#include "../inc/commands/PASS.hpp"
#include "../inc/commands/CAP.hpp"
#include "../inc/commands/NICK.hpp"
#include "../inc/commands/USER.hpp"
#include "../inc/commands/MODE.hpp"
#include "../inc/commands/PING.hpp"
#include "../inc/commands/PRIVMSG.hpp"
#include "../inc/commands/JOIN.hpp"
#include "../inc/commands/TOPIC.hpp"
#include "../inc/commands/PART.hpp"
#include "../inc/commands/QUIT.hpp"
#include "../inc/commands/INVITE.hpp"

Parser::Parser(Server& server_ref, Client& client_ref){
    //Incializa a lista de commandos...
    this->list_commands = get_list_commands();

    int i = 0;
    std::stringstream ss(client_ref.getMessage());
    std::string response;
    std::string cmd;
    
    while (std::getline(ss, response, ' ')){
        if (!response.empty()){
            if (i == 0){
                cmd = response;
                std::cout << "Command: " << response << std::endl;   
                
                //Incia o parsing do commandos...
                this->Parser_start(server_ref, client_ref, cmd);
                return;
            }
            i++;
        }
    }
}

Parser::~Parser(){
    std::map<std::string, Command *>::iterator it;
    for (it = this->list_commands.begin(); it != this->list_commands.end(); it++){
        delete it->second;
    }
    this->list_commands.clear();
}

std::map<std::string, Command *> Parser::get_list_commands(){
    std::map<std::string, Command*> commands;

    commands["CAP"]     = new CAP();
    commands["PASS"]    = new PASS();
    commands["NICK"]    = new NICK();
    commands["USER"]    = new USER();
    commands["MODE"]    = new MODE();
    commands["PING"]    = new PING();
    commands["PRIVMSG"] = new PRIVMSG();
    commands["JOIN"]    = new JOIN();
    commands["TOPIC"]   = new TOPIC();
    commands["PART"]    = new PART();
    commands["QUIT"]    = new QUIT();
    commands["INVITE"]  = new INVITE();
    return (commands);
}

void Parser::Parser_start(Server& server_ref, Client& client_ref, std::string cmd){
    std::vector<std::string> args;
    std::stringstream ss(client_ref.getMessage());
    std::string argument;

    bool isCmdUSER = false;

    if (cmd == "USER" || cmd == "TOPIC"){
        isCmdUSER = true;
    }
    //Listando os argumentos...
    while(std::getline(ss, argument, ' ')){
        if (!argument.empty()){
            if (argument.compare(cmd) != 0){
                if (argument.at(0) == ':' && argument.size() > 1){
                    int pos;

                    pos = ss.str().find(':');
                    if (!isCmdUSER){pos++;}
                    argument = ss.str().substr(pos);
                    args.push_back(argument);
                    break;
                }
                args.push_back(argument);
            }
        }
    }
    
    //Verificando se o comando existe.
    if (this->list_commands[cmd]){
        std::vector<std::string>::iterator it = args.begin();

        std::cout << "ARGS: " << std::endl;
        while (it != args.end()){
            std::cout << *it << std::endl;
            it++;
        }
        //Verifica se o cliente tentou executar outro comando sem ser autenticado.
        if ((cmd != "PASS" && cmd  != "NICK" && cmd != "USER" 
            && cmd != "CAP") && !client_ref.isAuthenticated()){

            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTREGISTERED, cmd, "You have not registered");
            return;
        }
        //Roda o comando com os argumentos
        this->list_commands[cmd]->run_command(server_ref, client_ref, args);
    }
    else{
        send_irc_reply(client_ref, server_ref.get_Servername(), ERR_UNKNOWNCOMMAND, cmd, "Unknown " + cmd);
    }
}
