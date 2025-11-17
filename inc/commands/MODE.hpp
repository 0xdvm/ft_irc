/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:17:53 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/17 19:21:58 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
#define MODE_HPP

#include "Command.hpp"
class MODE: public Command{
    public:
        MODE();
        ~MODE();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};
#endif