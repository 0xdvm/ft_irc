/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:34:20 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/09 22:27:56 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Client.hpp"
#include <vector>

class Server{
  private:
  int server_fd;
    std::string _port;
    std::string _password;
    std::vector<Client> list_clients;
    
    static bool _monitoring;
    static void handle_monitoring(int sigint);
  public:
    Server();
    Server(const Server& other);
    Server(std::string port, std::string password);
    ~Server(); 

    Server& operator=(const Server& other);

    void run_server();
};