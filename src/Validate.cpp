/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:22:26 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:15:14 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Validate.hpp"
#include <limits>
#include <sstream>

void	Validate::validatePortNumber(const std::string &port)
{
	std::stringstream ss(port);
	int number = 0;
	ss >> number;
	
	//Verifica se a conversão da porta para inteiro falhou.
	//Também verifica se passou o limite máximo de um unsigned short.
	if (ss.fail() || !ss.eof() || number < 0 || number > std::numeric_limits<unsigned short>::max())
	{
		throw std::runtime_error("Wrong port number!");
	}
}
