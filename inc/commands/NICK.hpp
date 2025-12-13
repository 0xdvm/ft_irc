/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:21:24 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:34:33 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
#define NICK_HPP

#include "Command.hpp"

class NICK: public Command{
    public:
        NICK();
        ~NICK();
        
        void            run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
        bool            isvalidNickname(std::string nickname);
        bool            isFreeNick(Server& server_ref, std::string nickname);
};
#endif