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

class Parser{
    private:
        
        void Parser_start(const Server& server_ref, Client& client_ref, std::string Parser);
    public:
        Parser(const Server& server_ref, Client& client_ref);
        ~Parser();
};
#endif