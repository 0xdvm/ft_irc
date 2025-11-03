/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Validate.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcsilv <marcsilv@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:20:36 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/03 15:47:25 by marcsilv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Validate.hpp"
#include <climits>
#include <cstddef>
#include <cstdlib>

Validate &Validate::operator=(const Validate &other) {
	/*std::cout << "Validate's Copy assignment operator called" << std::endl;*/
	if (this != &other) { }
	return (*this);
}

Validate::Validate(const Validate &other) {
	/*std::cout << "Validate's copy constructor operator called" << std::endl;*/

	*this = other;
}

Validate::Validate(void) {
	/*std::cout << "Validate's default constructor called"<< std::endl;*/
}
Validate::~Validate(void) {
	/*std::cout << "Validate's default destructor called" << std::endl;*/
}

bool	Validate::isAllNums(const std::string &nums)
{
	for (size_t i = 0; i < nums.length(); ++i)
		if (!std::isdigit(nums[i]))
			return (false);
	return (true);
}

void	Validate::validatePortNumber(const std::string &port)
{
	int number = atoi(port.c_str());
	if (!isAllNums(port) || number < 0 || number > USHRT_MAX)
		throw std::runtime_error("Wrong port number!");
}
