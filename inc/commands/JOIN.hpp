/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:32:12 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:30:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
#define JOIN_HPP

#include "Command.hpp"

class JOIN: public Command{
    public:
        JOIN();
        ~JOIN();
        void                run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif