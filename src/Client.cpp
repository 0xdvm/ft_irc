/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:49:57 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 11:33:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"

Client::Client():   _nickname(""), 
                    _username(""), 
                    _realname(""),
                    _message(""), 
                    _host(""), 
                    _servername(""),
                    _passReceived(false), 
                    _nickReceived(false), 
                    _userReceived(false),
                    _isAuthenticated(false), buffer(""){}

Client::~Client(){}

//Getters
bool Client::isAuthenticated()
{
    return (this->_isAuthenticated);
}

bool Client::hasPass()
{
    return (this->_passReceived);
}

bool Client::hasNick()
{
    return (this->_nickReceived);
}

bool Client::hasUser()
{
    return (this->_userReceived);
}

int& Client::get_fd()
{
    return (this->fd);
}

std::string Client::getNickname()
{
    return (this->_nickname);
}

std::string Client::getUsername()
{
    return (this->_username);
}

std::string Client::getRealname()
{
    return (this->_realname);
}

std::string Client::getMessage()
{
    return (this->_message);
}
std::string Client::getHost()
{
    return (this->_host);
}
std::string Client::getServername()
{
    return (this->_servername);
}

std::string Client::userMask()
{
    return (this->_nickname + "!" + this->_username + "@" + this->_host);
}

//Setters
void Client::set_fd(int fd)
{
    this->fd = fd;
}

void Client::setAuthenticated(bool v)
{
    this->_isAuthenticated = v;
}

void Client::setPass(bool v)
{
    this->_passReceived = v;
}

void Client::setNick(bool v)
{
    this->_nickReceived = v;
}

void Client::setUser(bool v)
{
    this->_userReceived = v;
}

void Client::setNickname(std::string& nickname)
{
    this->_nickname = nickname;
}

void Client::setUsername(std::string& username)
{
    this->_username = username;
}

void Client::setRealname(std::string& realname)
{
    this->_realname = realname;
}

void Client::setMessage(std::string& Message)
{
    this->_message = Message;
}

void Client::setHost(std::string& host)
{
    this->_host = host;
}

void Client::setServername(std::string& servername)
{
    this->_servername = servername;
}