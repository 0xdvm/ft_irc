/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:19:09 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:19:09 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
#define PART_HPP

#include "Command.hpp"

class PART: public Command{
    public:
        PART();
        ~PART();

        void            run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif
