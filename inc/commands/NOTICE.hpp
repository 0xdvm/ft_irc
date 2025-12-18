/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NOTICE.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:28:58 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/18 11:46:15 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICE_HPP
#define NOTICE_HPP


#include "Command.hpp"

class NOTICE: public Command
{
    public:
        NOTICE();
        ~NOTICE();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif