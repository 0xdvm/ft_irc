/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:38:59 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/13 21:26:00 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "Client.hpp"

void send_irc_reply(Client& client_ref, std::string prefix, std::string command, std::string dest, const std::string& message);

#endif