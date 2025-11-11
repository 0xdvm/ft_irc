/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:53:36 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/10 21:11:01 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
#define CMD_HPP

#include "../inc/Client.hpp"
#include <iostream>

class Cmd{
    private:
        std::string password;
    public:
        Cmd();
        Cmd(std::string password);
        Cmd(const Cmd& other);
        ~Cmd();

        Cmd& operator=(const Cmd& other);
        void parser(Client& client);
        void cmd_start(Client& client, std::string cmd, int size_args);
};
#endif