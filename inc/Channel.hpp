/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:37 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/17 20:33:53 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>
#include <list>
#include <vector>
#include <map>

class Server;
class Client;

class Channel{
    private:
        std::string                             _channelName;
        std::string                             _password;
        std::string                             _topic;
        std::string                             _topic_by;
        std::map<std::string, Client>           _memberList;
        std::list<std::string>                  _inviteList;
        
        std::list<char>                         _list_actives_modes;
        std::list<std::string>                  _list_actives_modes_args;
        
        std::list<char>                         _list_mode;
        std::list<std::string>                  _list_mode_args;
        
        //Modos
        bool                                    _topic_mode;
        bool                                    _invite_mode;
        bool                                    _key_mode;
        bool                                    _limit_mode;
        
        bool                                    _hasPassword;
        bool                                    _hasTopic; 
        int                                     _userLimit;     
        int                                     _memberNum;
        int                                     _limit_members;            
        long int                                _topic_time;

    public:
        Channel();
        Channel(std::string channelName);
        Channel(std::string channelName, std::string password);
        ~Channel();
        
        void                                    showModes(char opt, char mode, std::string args);
        void                                    joinChannel(Client&);
        void                                    executeMode(std::string type_mode, std::vector<std::string>::iterator &current_args, std::vector<std::string>::iterator end_args);
        void                                    addMember(std::string nickname, Client&);
        void                                    sendBroadcast(std::string command, std::string tosend, Client& client, bool isSendSelf);
        void                                    sendBroadcastQuit(std::string command, std::string tosend, Client& client, bool isSendSelf);
        void                                    setMemberNum(int num);
        void                                    addInviteList(std::string nickname);
        void                                    removeInviteList(std::string nickanem);
        //

        void                                    setModeActive(char opt, char mode, std::string args);
        void                                    setInvite(Client& nickname_dest, Client& client_send);
        void                                    setTopic(std::string topic);
        void                                    setUserlimit(std::string nickname, int limit);
        void                                    setOperator(std::string nickname, std::string nickaname_dest, bool value);
        void                                    setTopicby(std::string nick);
        void                                    setTopicTime(long int time);
        void                                    removeMember(std::string nickname);
        
        bool                                    getTopicMode();
        bool                                    getInviteMode();
        bool                                    isInvited(std::string nickname);
        bool                                    getKeyMode();
        bool                                    getLimitMode();
        
        bool                                    addOperator(std::string);
        bool                                    removeOperator(std::string);
        bool                                    isMember(std::string nickname);
        bool                                    isCorrectpassword(std::string password);
        bool                                    hasPassword();
        bool                                    hasTopic();
        bool                                    isOperator(std::string nickname);
        Client&                                 getClient(std::string nickname, Server& server_ref);
        std::string                             getChannelName();
        std::string                             getListmember();
        std::string                             getTopic();
        std::string                             getTopicby();
        std::string                             getTopicTime();
        std::string                             getCurrentMode(std::list<char> &list_modes, std::list<std::string> &args, bool clean);
        std::string                             getActiveMode();
        std::string                             getModeinstance();
        int                                     getMemberNum();

};
#endif