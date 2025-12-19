/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:19:35 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:19:35 by dvemba           ###   ########.fr       */
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