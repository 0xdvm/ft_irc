/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 16:20:57 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/15 19:43:12 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "Command.hpp"

class USER: public Command{
    public:
        USER();
        ~USER();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
        bool isValidUsername(std::string& username);
        bool isValidRealname(std::string& realname);
};

#endif