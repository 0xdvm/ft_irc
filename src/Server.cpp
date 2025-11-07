/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:31:48 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/07 12:42:05 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

Server::Server(){}

Server::Server(const Server& other){
    *this = other;
}
Server::Server(std::string port, std::string password): _port(port), _password(password){
    
}

Server::~Server(){}

Server& Server::operator=(const Server& other){
    if (this != &other){
        this->_password = other._password;
        this->_port = other._port;
        this->socket_fd = other.socket_fd;
    }
    return (*this);
}

void Server::run_server(){
    struct addrinfo hints, *res, *p;
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(NULL, this->_port.c_str(), &hints, &res);
    
    for(p = res; p != NULL; p = p->ai_next){
        this->socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->socket_fd == -1){
            continue;
        }
        int opt = 1;
        
        if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
            close(this->socket_fd);
            continue;
        }
        
        if (bind(this->socket_fd, p->ai_addr, p->ai_addrlen) == 0){
            break;
        }
        close(this->socket_fd);
    }

    if (listen(this->socket_fd, 128) < 0){
        throw std::runtime_error("listen");
    }
    freeaddrinfo(res);
    close(this->socket_fd);
}

