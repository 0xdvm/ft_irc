/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CAP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:26:41 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/14 21:30:09 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAP_HPP
#define CAP_HPP

#include "Command.hpp"
class CAP: public Command{
    public:
        CAP();
        ~CAP();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};
#endif