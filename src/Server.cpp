/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:31:48 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/15 18:48:16 by dvemba           ###   ########.fr       */
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
#include <errno.h>
#include <stdio.h>

#include "../inc/Parser.hpp"

bool Server::_monitoring = true;  

Server::Server(std::string servername, std::string port, std::string password):_servername(servername), _port(port), _password(password){}

Server::~Server(){}

void Server::handle_monitoring(int sigint){
    (void)sigint;
    Server::_monitoring = false;
}

Client& Server::get_client(int fd){
    return (this->list_clients[fd]);
}

std::string& Server::get_password(){
    return (this->_password);
}
std::string& Server::get_Servername(){
    return (this->_servername);
}

std::map<int, Client> Server::getListClient(){
    return (this->list_clients);
}

void Server::read_client(char* buffer, int size_buf, Client& client) {
    // Adiciona dados recebidos ao buffer do cliente
    client.buffer.append(buffer, size_buf);

    size_t pos;
    while ((pos = client.buffer.find("\r\n")) != std::string::npos || 
           (pos = client.buffer.find("\n")) != std::string::npos) {
        // Extrai a mensagem até o final de linha
        std::string message = client.buffer.substr(0, pos);
        client.setMessage(message);
    
        Parser Parser(*this, client);
        // std::cout << "Mensagem recebida: " << message << std::endl;

        // Remove a mensagem processada do buffer
        client.buffer.erase(0, pos + ((client.buffer[pos] == '\r' && client.buffer[pos+1] == '\n') ? 2 : 1));
    }
}

void Server::run_server(){
    
    std::cout << "Start server..." << std::endl;
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
        this->_server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->_server_fd == -1){
            continue;
        }
        int opt = 1;
        
        if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
            close(this->_server_fd);
            continue;
        }
        
        if (bind(this->_server_fd, p->ai_addr, p->ai_addrlen) == 0){
            break;
        }
        close(this->_server_fd);
    }

    //Tornando o socket do servidor nao bloqueante.
    fcntl(this->_server_fd, F_SETFL, O_NONBLOCK);

    if (listen(this->_server_fd, 128) < 0){
        throw std::runtime_error("listen");
    }

    //Criando um epoll para monitorar os clientes que causerem um evento.
    epoll_fd = epoll_create1(0);

    //Criando um configuracao de monitoramento para o _server_fd.
    struct epoll_event ev;
    ev.data.fd = this->_server_fd;
    ev.events = EPOLLIN;

    //Adicionando o _server_fd epoll_fd para ser monitorado.
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, this->_server_fd, &ev);

    //Lista que serao adicionando os sockets que causaram evento ao servidor.
    struct epoll_event events[100];

    while (Server::_monitoring){
        //Esperando sockets causarem eventos e retorna o numero de sockets que causarao eventos.
        int n = epoll_wait(epoll_fd, events, 100, -1);

        for (int i = 0; i < n; i++){
            // Se o evento foi feito para o servidor (quer dizer que um cliente tentou se conectar).
            if (events[i].data.fd == this->_server_fd){
                int client_fd = accept(this->_server_fd, NULL, NULL);
                
                
                if (client_fd < 0){
                    if (errno == EWOULDBLOCK || errno == EAGAIN) {
                        // Não há clientes ainda, continue o loop
                        continue;
                    } else {
                        // Algum outro erro sério aconteceu
                        perror("accept");
                        continue;
                    }
                }
                //Tornando o client nao bloqueante.
                fcntl(client_fd, F_SETFL, O_NONBLOCK);
                
                struct epoll_event client_ev;
                client_ev.data.fd = client_fd;
                client_ev.events = EPOLLIN;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_ev);

                //Criando um objecto Client.
                Client client;

                //Setando o fd.
                client.set_fd(client_fd);
                
                //Adicionando o client na lista dos clientes.
                this->list_clients[client_fd] = client;
            }
            else{// Se for outro evento qualquer (cliente enviou mensagem, cliente se desconectou do serivdor).

                char buffer[1024];
                //Le a mensagem enviada ao servidor.
                int size_buf = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                
                //Se houver um erro ou desconecxao com o servidor.
                int fd = events[i].data.fd; // use o fd correto
                if (size_buf <= 0){
                    this->list_clients.erase(fd);
                    close(events[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    continue;
                }
                this->read_client(buffer, size_buf, this->get_client(fd));
            }
        }
    }

    std::cout << std::endl << "Close server..." << std::endl;

    //Desconecta os clientes conectados ao servidor...
    for (std::map<int, Client>::iterator it = list_clients.begin(); it != list_clients.end(); ++it)
        close(it->first);
    
    freeaddrinfo(res);
    close(this->_server_fd);
    close(epoll_fd);
}

