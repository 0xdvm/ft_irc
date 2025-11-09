/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:49:57 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/09 21:08:52 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/Client.hpp"

Client::Client(){
    this->authenticated = false;
    this->buffer = "";
}

Client::Client(const Client& other){
    *this = other;
}

Client::~Client(){}

Client& Client::operator=(const Client& other){
    if (this != &other){
        this->authenticated = other.authenticated;
        this->fd = other.fd;
        this->username = other.username;
        this->nickname = other.nickname;   
    }
    return (*this);
}

