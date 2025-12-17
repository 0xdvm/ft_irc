<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:45:41 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:34:57 by dvemba           ###   ########.fr       */
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

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PING.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:45:41 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/17 19:47:42 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_HPP
#define PING_HPP

#include "Command.hpp"

class PING: public Command{
    public:
        PING();
        ~PING();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

>>>>>>> main
#endif