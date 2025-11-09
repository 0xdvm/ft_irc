/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:25:00 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/09 21:07:11 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client{
    private:
        std::string username;
        std::string nickname;
        std::string buffer;
        bool authenticated;
        int fd;
    public:
        Client();
        Client(const Client& other);
        ~Client();

        Client& operator=(const Client& other);
        
};
#endif