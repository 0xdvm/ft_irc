/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 20:25:00 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/24 20:52:07 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class Client{
    private:
        int fd;
        
        std::string _nickname;
        std::string _username;
        std::string _realname;
        std::string _message;
        std::string _host;
        std::string _servername;
        
        bool _passReceived;
        bool _nickReceived;
        bool _userReceived;
        bool _isAuthenticated;
    public:
        std::string buffer;
        Client();
        ~Client();

        int& get_fd();
        bool hasPass();
        bool hasNick();
        bool hasUser();
        bool isAuthenticated();
        std::string getNickname();
        std::string getUsername();
        std::string getRealname();
        std::string getMessage();
        std::string getHost();
        std::string getServername();
        std::string userMask();
        
        void setPass(bool v);
        void setNick(bool v);
        void setUser(bool v);
        void setAuthenticated(bool v);
        void set_fd(int fd);
        void setNickname(std::string&);
        void setUsername(std::string&);
        void setRealname(std::string&);
        void setMessage(std::string&);
        void setHost(std::string&);
        void setServername(std::string&);
        
};
#endif