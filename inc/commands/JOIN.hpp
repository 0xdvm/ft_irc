/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:18:55 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:18:55 by dvemba           ###   ########.fr       */
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