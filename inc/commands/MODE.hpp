/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:19:00 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:19:00 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODE_HPP
#define MODE_HPP

#include "Command.hpp"
class MODE: public Command{
    private:
        std::vector<std::string> arguments_modes;
        std::vector<std::string> list_modes;
    public:
        MODE();
        ~MODE();
        
        void validateModes(std::vector<std::string> args);
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};
#endif