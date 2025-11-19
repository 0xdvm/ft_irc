/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:44:32 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/19 11:23:11 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "Command.hpp"

class PRIVMSG:  public Command{
  public:
    PRIVMSG();
    ~PRIVMSG();
    void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};
#endif