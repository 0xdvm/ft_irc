/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 17:01:32 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 17:01:32 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
#define INVITE_HPP

#include "Command.hpp"
class Channel;

class INVITE: public Command{
    public:
        INVITE();
        ~INVITE();
        void                run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
