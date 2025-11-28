/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:37 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/27 12:32:06 by dvemba           ###   ########.fr       */
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
        std::map<std::string, Client>           _memberList;
        std::list<std::string>                  _inviteList;
        int                                     _memberNum;

        //Modos
        bool                                    _inviteOnly;
        bool                                    _hasPassword;
        bool                                    _hasTopic; 
        int                                     _userLimit;     

    public:
        Channel();
        Channel(std::string channelName);
        Channel(std::string channelName, std::string password);
        ~Channel();
        
        void                                    joinChannel(Client&);
        void                                    addMember(std::string nickname, Client&);
        void                                    sendBroadcast(std::string command, std::string tosend, Client& client, bool isSendSelf);
        void                                    setMemberNum(int num);
        void                                    addInviteList(std::string nickname);
        void                                    removeInviteList(std::string nickanem);
        //                      
        void                                    setInvite(std::string nickname, std::string nickaname_dest);
        void                                    setTopic(std::string nickname, std::string topic);
        void                                    setUserlimit(std::string nickname, int limit);
        void                                    setOperator(std::string nickname, std::string nickaname_dest, bool value);
                                
        Client&                                 getClient(std::string nickname);
        bool                                    addOperator(std::string);
        bool                                    isMember(std::string nickname);
        void                                    removeMember(std::string nickname);
        bool                                    isCorrectpassword(std::string password);
        bool                                    hasPassword();
        bool                                    hasTopic();
        bool                                    isOperator(std::string nickname);
        std::string                             getChannelName();
        std::string                             getListmember();
        int                                     getMemberNum();

};
#endif