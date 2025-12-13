/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:34:20 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 15:34:08 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "Client.hpp"
#include <map>
#include <list>
#include "Channel.hpp"

class Server{
    private:
      int                                       _server_fd;
      std::string                               _servername;
      std::string                               _port;
      std::string                               _password;
      std::map<int, Client>                     list_clients;
      std::list<Channel*>                       _channels;
      
      static bool                               _monitoring;
      static void                               handle_monitoring(int sigint);
      Client&                                   get_client(int fd);
    public:
      Server(std::string servername, std::string port, std::string password);
      ~Server();
      
      
      Channel&                                   findChannel(std::string& channel);
      Channel&                                   createChannel(std::string& channel);
      Client&                                    findUser(std::string&);
      std::string&                               get_password();
      std::string&                               get_Servername();
      std::list<Channel*>&                       getListChannel();
      std::map<int, Client>                      getListClient();
      
      void                                       read_client(char* buffer, int size_buf, Client& client);
      void                                       removeChannel(std::string channel);
      void                                       run_server();
};
#endif