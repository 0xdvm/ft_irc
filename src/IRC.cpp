/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:29:52 by marcsilv          #+#    #+#             */
/*   Updated: 2025/11/03 17:44:10 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRC.hpp"
#include <cstdlib>
#include <stdexcept>
#include <string>

IRC::IRC(void) {
	/*std::cout << "IRC's default constructor called"<< std::endl;*/
}

IRC::IRC(const IRC &other) {
	/*std::cout << "IRC's copy constructor operator called" << std::endl;*/
	*this = other;
}

IRC::IRC(const std::string &port, const std::string &password): _password(password) {
	_validation.validatePortNumber(port);
}

IRC::~IRC(void) {
	/*std::cout << "IRC's default destructor called" << std::endl;*/
}

IRC &IRC::operator=(const IRC &other) {
	/*std::cout << "IRC's Copy assignment operator called" << std::endl;*/
	if (this != &other) {
		this->_validation = other._validation;
		this->_port = other._port;
		this->_password = other._password;
	}
	return (*this);
}

void	IRC::run(void) {

}
