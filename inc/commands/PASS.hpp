/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:20:04 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/14 20:50:14 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
#define PASS_HPP

#include "Command.hpp"

class PASS: public Command{
  public:
    PASS();
    ~PASS();
    void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};
#endif