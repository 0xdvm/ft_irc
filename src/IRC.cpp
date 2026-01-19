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

IRC::IRC(const std::string servername, const std::string &port, const std::string &password)
{
	_validation.validatePortNumber(port);
	if (password.empty()){throw std::runtime_error("Invalid Password!");}

	this->_password = password;
	this->_port = port;
	this->_servername = servername;
}
void	IRC::run(void) 
{
	Server server("ircserv", this->_port, this->_password);
	server.run_server();
}
