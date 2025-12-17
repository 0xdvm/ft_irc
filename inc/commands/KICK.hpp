/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:43:08 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/17 20:43:09 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
#define KICK_HPP

#include "Command.hpp"
class Channel;

class KICK: public Command{
    public:
        KICK();
        ~KICK();
        void                run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
