/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:46:19 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:38:24 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/Command.hpp"

Command::Command(const int num_args): num_args(num_args){}

Command::~Command(){}

int Command::get_num_args() const {return (this->num_args);}
