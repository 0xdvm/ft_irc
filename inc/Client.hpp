/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:25:00 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/10 10:23:14 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client{
    private:
        std::string username;
        std::string nickname;
        bool authenticated;
        int fd;
    public:
        std::string buffer;
        Client();
        Client(const Client& other);
        ~Client();

        Client& operator=(const Client& other);

        void set_fd(int fd);
        bool isAuthenticated();
        
};
#endif