/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:31:48 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/18 19:58:55 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

#include <netdb.h>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>

#include <signal.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <stdio.h>

#include <algorithm>

#include "../inc/Parser.hpp"

bool Server::_monitoring = true;  

Server::Server(std::string servername, std::string port, std::string password):_servername(servername), _port(port), _password(password){}

Server::~Server()
{
    std::list<Channel *>::iterator it;
    
    for (it = this->_channels.begin(); it != this->_channels.end(); it++)
    {
        delete *it;
    }
    this->_channels.clear();
}

void Server::handle_monitoring(int sigint)
{
    (void)sigint;
    Server::_monitoring = false;
}

Client& Server::get_client(int fd)
{
    return (this->list_clients[fd]);
}

std::string& Server::get_password()
{
    return (this->_password);
}
std::string& Server::get_Servername()
{
    return (this->_servername);
}

std::map<int, Client> Server::getListClient()
{
    return (this->list_clients);
}
std::list<Channel*>& Server::getListChannel()
{
    return(this->_channels);
}

Client& Server::findClient(std::string& nickname)
{
    std::map<int, Client>::iterator it = this->list_clients.begin();

    while (it != this->list_clients.end())
    {
        if (nickname.compare(it->second.getNickname()) == 0)
        {
            return (it->second);
        }
        it++;
    }
    return (this->list_clients[-1]);
}

Client& Server::findUser(std::string& nickname)
{
    std::map<int, Client>::iterator it = this->list_clients.begin();

    while (it != this->list_clients.end())
    {
        if (nickname.compare(it->second.getNickname()) == 0)
        {
            return (it->second);
        }
        it++;
    }
    throw std::runtime_error("User not found");
}

Channel& Server::findChannel(std::string& channel)
{
    std::list< Channel*>::iterator it;

    it = this->_channels.begin();
    while (it != this->_channels.end())
    {
        if ((*it)->getChannelName().compare(channel) == 0)
        {
            return (*(*it));
        }
        it++;
    }
    throw std::runtime_error("Channel not found");
}

Channel& Server::createChannel(std::string& channel)
{
    // this->channels[channel] = Channel (channel);
    // if (password.empty())
    // {
        Channel *chl = new Channel(channel);
        this->_channels.push_back(chl);
        return (*chl);    
    // }
    // Channel *chl = new Channel(channel, password);
    // this->_channels.push_back(chl);
    // return (*chl);    
}

void Server::removeChannel(std::string channel)
{
    std::list< Channel*>::iterator it;

    it = this->_channels.begin();
    while (it != this->_channels.end())
    {
        if ((*it)->getChannelName() == channel)
        {
            Channel *n_it = *it;
            it = this->_channels.erase(it);
            delete n_it;
            return;
        }
        else
            it++;
    }
}

void Server::read_client(char* buffer, int size_buf, Client& client)
{
    // Adiciona dados recebidos ao buffer do cliente
    client.buffer.append(buffer, size_buf);

    size_t pos;
    while ((pos = client.buffer.find("\r\n")) != std::string::npos) 
    // || (pos = client.buffer.find("\n")) != std::string::npos)
    {
        // Extrai a mensagem até o final de linha
        std::string message = client.buffer.substr(0, pos);
        client.setMessage(message);
    
        Parser Parser(*this, client);
        // std::cout << "Mensagem recebida: " << message << std::endl;

        // Remove a mensagem processada do buffer
        client.buffer.erase(0, pos + ((client.buffer[pos] == '\r' && client.buffer[pos+1] == '\n') ? 2 : 1));
    }
}

void Server::run_server()
{
    
    std::cout << "Start server..." << std::endl;
    struct addrinfo hints, *res, *p;
    int epoll_fd;
    int _bind;
    
    //Capturando o signal ctrl + c para sair do loop e encerrar adequadamente o programa.
    signal(SIGINT, Server::handle_monitoring);
    signal(SIGPIPE, SIG_IGN);

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    
    if (getaddrinfo(NULL, this->_port.c_str(), &hints, &res) != 0 )
    {
        perror("getaddrinfo");
        return;
    }
    
    for(p = res; p != NULL; p = p->ai_next)
    {
        this->_server_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->_server_fd == -1)
        {
            continue;
        }
        int opt = 1;
        
        if (setsockopt(this->_server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        {
            close(this->_server_fd);
            continue;
        }
        _bind = bind(this->_server_fd, p->ai_addr, p->ai_addrlen);
        if (_bind == 0)
        {
            break;
        }
        close(this->_server_fd);
    }
    
    if (_bind < 0)
    {
        freeaddrinfo(res);
        close(this->_server_fd);
        throw std::runtime_error("It was not possible to perform the bind.");
    }
    
    //Tornando o socket do servidor nao bloqueante.
    if(fcntl(this->_server_fd, F_SETFL, O_NONBLOCK) == -1)
    {
        freeaddrinfo(res);
        close(this->_server_fd);
        perror("fcntl");
        return;
    }

    if (listen(this->_server_fd, 128) < 0)
    {
        freeaddrinfo(res);
        close(this->_server_fd);
        throw std::runtime_error("It was not possible to perform the listen.");
    }

    //Criando um epoll para monitorar os clientes que causerem um evento.
    epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) 
    {
        freeaddrinfo(res);
        close(this->_server_fd);
        perror("epoll_create1");
        return;
    }

    //Criando um configuracao de monitoramento para o _server_fd.
    struct epoll_event ev;
    ev.data.fd = this->_server_fd;
    ev.events = EPOLLIN;

    //Adicionando o _server_fd epoll_fd para ser monitorado.
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, this->_server_fd, &ev);

    //Lista que serao adicionando os sockets que causaram evento ao servidor.
    struct epoll_event events[100];

    while (Server::_monitoring)
    {
        //Esperando sockets causarem eventos e retorna o numero de sockets que causarao eventos.
        int n = epoll_wait(epoll_fd, events, 100, -1);
        
        for (int i = 0; i < n; i++)
        {
            // Se o evento foi feito para o servidor (quer dizer que um cliente tentou se conectar).
            if (events[i].data.fd == this->_server_fd)
            {
                int client_fd = accept(this->_server_fd, NULL, NULL);
                
                if (client_fd < 0)
                {
                    // Algum erro sério aconteceu
                    perror("accept");
                    continue;
                }
                //Tornando o client nao bloqueante.
                if(fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1){
                    perror("fcntl");
                    continue;
                }
                
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
            else
            {// Se for outro evento qualquer (cliente enviou mensagem, cliente se desconectou do serivdor).

                char buffer[1024];
                //Le a mensagem enviada ao servidor.
                int size_buf = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                
                //Se houver um erro ou desconecxao com o servidor.
                int fd = events[i].data.fd; // use o fd correto
                if (size_buf <= 0)
                {
                    this->list_clients.erase(fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    close(events[i].data.fd);
                    continue;
                }
                this->read_client(buffer, size_buf, this->get_client(fd));
            }
        }
    }

    std::cout << std::endl << "Close server..." << std::endl;

    //Desconecta os clientes conectados ao servidor...
    for (std::map<int, Client>::iterator it = list_clients.begin(); it != list_clients.end(); ++it){close(it->first);}
    
    freeaddrinfo(res);
    close(epoll_fd);
    close(this->_server_fd);
}
