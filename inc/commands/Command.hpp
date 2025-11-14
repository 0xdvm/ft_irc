/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:46:35 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/12 21:19:41 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>
#include "../Server.hpp"
#include "../Client.hpp"

class Command{
  private:
    const int num_args;
  public:
    Command(int num_args);
    virtual ~Command();
    
    virtual void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args) const = 0;
    int get_num_args() const;
};
#endif