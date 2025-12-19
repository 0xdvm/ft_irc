/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WHO.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:11:36 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:14:26 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHO_HPP
#define WHO_HPP

#include "Command.hpp"

class WHO: public Command
{
    public:
        WHO();
        ~WHO();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
