/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:53:36 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/10 10:18:34 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_HPP
#define CMD_HPP

#include "../inc/Client.hpp"
#include <iostream>

void parser(Client& client);
void cmcmd_startd(Client& client, std::string cmd, int size_args);
#endif