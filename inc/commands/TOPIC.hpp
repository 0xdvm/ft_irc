/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 09:31:10 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:30:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

class TOPIC: public Command
{
    public:
        TOPIC();
        ~TOPIC();

        void                run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};