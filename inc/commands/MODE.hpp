/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:17:53 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:34:45 by dvemba           ###   ########.fr       */
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