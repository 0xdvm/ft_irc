/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:37 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/25 17:30:32 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <list>
#include <map>
#include "Client.hpp"

class Channel{
    private:
        std::string                             _channelName;
        std::string                             _password;
        std::string                             _topic;
        // std::list<std::string>      _operatorsList;
        std::map<std::string, Client>           _memberList;
        std::list<std::string>                  _bannedList;
        int                                     _memberNum;

        bool                                    _hasPassword;
        bool                                    _hasTopic;
    public:
        Channel();
        Channel(std::string channelName);
        Channel(std::string channelName, std::string password);
        ~Channel();
        
        void            joinChannel(Client&);
        bool            addOperator(std::string);
        void            addMember(std::string nickname, Client&);
        void            sendBroadcast(std::string command, std::string tosend, Client& client);
        void            setTopic(std::string topic);
        
        void            setMemberNum(int num);
        int             getMemberNum();
        bool            isMember(std::string nickname);
        bool            hasPassword();
        bool            hasTopic();
        bool            isCorrectpassword(std::string password);
        std::string     getChannelName();
        std::string     getListmember();
};
#endif