/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:37 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/24 20:59:02 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <list>
#include "Client.hpp"

class Channel{
    private:
        std::string                 _channelName;
        std::string                 _password;
        std::string                 _topic;
        std::list<std::string>      _operatorsList;
        std::list<Client>           _memberList;
        std::list<std::string>      _bannedList;
        int                         _memberNum;

        bool                        _hasPassword;
    public:
        Channel();
        Channel(std::string channelName);
        Channel(std::string channelName, std::string password);
        ~Channel();
        
        void            joinChannel(Client&);
        void            addOperator(std::string);
        void            addMember(Client&);
        void            sendBroadcast(std::string command, std::string tosend, Client& client);
        
        void            setMemberNum(int num);
        int             getMemberNum();
        bool            isMember(std::string nickname);
        bool            hasPassword();
        bool            isCorrectpassword(std::string password);
        std::string     getChannelName();
};
#endif