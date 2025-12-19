/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 10:20:00 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/19 10:20:00 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commands/Command.hpp"

Command::Command(const int num_args): num_args(num_args){}

Command::~Command(){}

int Command::get_num_args() const {return (this->num_args);}
