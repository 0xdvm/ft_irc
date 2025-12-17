/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 11:22:26 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/11 11:22:28 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Validate.hpp"
#include <climits>
#include <limits>

#include <cstddef>
#include <cstdlib>
#include <sstream>


Validate::Validate(void) {
	/*std::cout << "Validate's default constructor called"<< std::endl;*/
}
Validate::Validate(const Validate &other) {
	/*std::cout << "Validate's copy constructor operator called" << std::endl;*/
	
	*this = other;
}

Validate::~Validate(void) {
	/*std::cout << "Validate's default destructor called" << std::endl;*/
}

Validate &Validate::operator=(const Validate &other) {
	/*std::cout << "Validate's Copy assignment operator called" << std::endl;*/
	if (this != &other) { }
	return (*this);
}

void	Validate::validatePortNumber(const std::string &port)
{
	std::stringstream ss(port);
	int number = 0;

	ss >> number;
	
	//Verifica se a conversão da porta para inteiro falhou.
	//Também verifica se passou o limite máximo de um unsigned short.
	if (ss.fail() || !ss.eof() || number < 0 || number > std::numeric_limits<unsigned short>::max()){
		throw std::runtime_error("Wrong port number!");
	}
}
