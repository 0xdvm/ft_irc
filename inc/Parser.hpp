/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:53:36 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/11 09:29:18 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "../inc/Client.hpp"
#include "../inc/Server.hpp"

#include <iostream>
#include <map>
#include "./commands/Command.hpp"

class Parser{
    private:
        std::map<std::string, Command *> list_commands;
        std::map<std::string, Command *> get_list_commands();
        void Parser_start(Server& server_ref, Client& client_ref, std::string Parser);
    public:
        Parser(Server& server_ref, Client& client_ref);
        ~Parser();
};
#endif