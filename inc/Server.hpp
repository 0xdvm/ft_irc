/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:34:20 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/14 20:12:25 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include "Client.hpp"
#include <map>

class Server{
  private:
    int _server_fd;
    std::string _servername;
    std::string _port;
    std::string _password;
    std::map<int, Client> list_clients;
    
    static bool _monitoring;
    static void handle_monitoring(int sigint);
  public:
    Server(std::string servername, std::string port, std::string password);
    ~Server(); 
    
    Client& get_client(int fd);
    std::string& get_password();
    std::string& get_Servername();
    void read_client(char* buffer, int size_buf, Client& client);
    std::map<int, Client> getListClient();
    void run_server();
};
#endif