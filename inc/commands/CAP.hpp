/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:26:41 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:29:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAP_HPP
#define CAP_HPP

#include "Command.hpp"

class CAP: public Command{
    public:
        CAP();
        void        run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};
#endif