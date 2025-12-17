<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:57:48 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 12:29:25 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRC.hpp"
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "../inc/Server.hpp"

IRC::IRC(const std::string &port, const std::string &password): _password(password) 
{
	_validation.validatePortNumber(port);
	this->_port = port;
}
void	IRC::run(void) 
{
	Server server("ircserv", this->_port, this->_password);
	server.run_server();
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:57:48 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/12 20:57:50 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRC.hpp"
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "../inc/Server.hpp"

IRC::IRC(void) {}

IRC::IRC(const IRC &other) {
	*this = other;
}

IRC::IRC(const std::string &port, const std::string &password): _password(password) {
	_validation.validatePortNumber(port);
	this->_port = port;
}

IRC::~IRC(void) {}

IRC &IRC::operator=(const IRC &other) {
	if (this != &other) {
		this->_validation = other._validation;
		this->_port = other._port;
		this->_password = other._password;
	}
	return (*this);
}

void	IRC::run(void) {
	Server server("ircserv", this->_port, this->_password);

	server.run_server();
}
>>>>>>> main
