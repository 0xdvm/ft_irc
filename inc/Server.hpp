/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:34:20 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/09 17:49:42 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

class Server{
  private:
    std::string _port;
    std::string _password;
    int server_fd;

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