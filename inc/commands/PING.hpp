/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:19:19 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:19:19 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_HPP
#define PING_HPP

#include "Command.hpp"

class PING: public Command{
    public:
        PING();
        ~PING();
        
        void            run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif