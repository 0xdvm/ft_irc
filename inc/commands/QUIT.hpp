/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUIT.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:04:20 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/17 11:30:47 by marvin           ###   ########.fr       */
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
