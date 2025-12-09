/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgouveia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:03:59 by cgouveia          #+#    #+#             */
/*   Updated: 2025/12/09 19:04:09 by cgouveia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
#define PART_HPP

#include "Command.hpp"

class PART: public Command{
    public:
        PART();
        ~PART();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
