/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:31:48 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/09 18:19:28 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#include <signal.h>
#include <fcntl.h>
#include <sys/epoll.h>

Server::Server(){}

Server::Server(const Server& other){
    *this = other;
}

bool Server::_monitoring = true;  

Server::Server(std::string port, std::string password): _port(port), _password(password){
}

Server::~Server(){}

Server& Server::operator=(const Server& other){
    if (this != &other){
        this->_password = other._password;
        this->_port = other._port;
        this->server_fd = other.server_fd;
    }
    return (*this);
}

void Server::handle_monitoring(int sigint){
    (void)sigint;
    Server::_monitoring = false;
}

void Server::run_server(){
    
    std::cout << "Inciando o servidor..." << std::endl;
    struct addrinfo hints, *res, *p;
    int epoll_fd;
    
    //Capturando o signal ctrl + c para sair do loop e encerrar adequadamente o programa.
    signal(SIGINT, Server::handle_monitoring);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    getaddrinfo(NULL, this->_port.c_str(), &hints, &res);
    
    for(p = res; p != NULL; p = p->ai_next){
        this->server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->server_fd == -1){
            continue;
        }
        int opt = 1;
        
        if (setsockopt(this->server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
            close(this->server_fd);
            continue;
        }
        
        if (bind(this->server_fd, p->ai_addr, p->ai_addrlen) == 0){
            break;
        }
        close(this->server_fd);
    }

    //Tornando o socket do servidor nao bloqueante.
    fcntl(this->server_fd, F_SETFL, O_NONBLOCK);

    if (listen(this->server_fd, 128) < 0){
        throw std::runtime_error("listen");
    }

    //Criando um epoll para monitorar os clientes que causerem um evento.
    epoll_fd = epoll_create1(0);

    //Criando um configuracao de monitoramento para o server_fd.
    struct epoll_event ev;
    ev.data.fd = this->server_fd;
    ev.events = EPOLLIN;

    //Adicionando o server_fd epoll_fd para ser monitorado.
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, this->server_fd, &ev);

    //Lista que serao adicionando os sockets que causaram evento ao servidor.
    struct epoll_event events[100];

    while (Server::_monitoring){
        //Esperando sockets causarem eventos e retorna o numero de sockets que causarao eventos.
        int n = epoll_wait(epoll_fd, events, 100, -1);

        for (int i = 0; i < n; i++){
            // Se o evento foi feito para o servidor (quer dizer que um cliente tentou se conectar).
            if (events[i].data.fd == this->server_fd){
                //continue...
            }
            else{// Se for outro evento qualquer (cliente enviou mensagem, cliente se desconectou do serivdor).
                //continue...
            }
        }
    }

    std::cout << "Encerrando o servidor..." << std::endl;
    
    freeaddrinfo(res);
    close(this->server_fd);
    close(epoll_fd);
}

