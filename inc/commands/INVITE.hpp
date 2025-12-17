/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:38:34 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/17 20:38:37 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
#define INVITE_HPP

#include "Command.hpp"
class Channel;

class INVITE: public Command{
    public:
        INVITE();
        ~INVITE();
        void                run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
