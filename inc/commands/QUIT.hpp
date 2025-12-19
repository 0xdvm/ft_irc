/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:19:30 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:19:30 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
#define QUIT_HPP

#include "Command.hpp"

class QUIT: public Command{
    public:
        QUIT();
        ~QUIT();

        void            run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
