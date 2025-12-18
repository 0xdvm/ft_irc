/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:45:41 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:30:40 by marvin           ###   ########.fr       */
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