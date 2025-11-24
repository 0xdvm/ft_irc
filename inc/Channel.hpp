/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:37 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/24 15:15:39 by dvemba           ###   ########.fr       */
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
        std::list<Client>      _memberList;
        std::list<std::string>      _bannedList;
        int                         _memberNum;
    public:
        Channel();
        Channel(std::string channelName);
        ~Channel();
        
        void joinChannel(Client&);
        void            addOperator(std::string);
        void            addMember(Client&);
        std::string     getChannelName();

        void            setMemberNum(int num);
        int             getMemberNum();
        bool            isMember(std::string nickname);
};
#endif