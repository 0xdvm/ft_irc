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
#include <iostream>

class Parser{
    private:
        std::string password;
        
        void Parser_start(Client& client, std::string Parser, int size_args);
    public:
        Parser();
        Parser(Client& clien, std::string password);
        Parser(const Parser& other);
        ~Parser();

        Parser& operator=(const Parser& other);
};
#endif