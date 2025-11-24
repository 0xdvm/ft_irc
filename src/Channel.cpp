/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/24 15:16:58 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

Channel::Channel() : _channelName("") {}

Channel::Channel(std::string channelName):_channelName(channelName){}

Channel::~Channel(){}

void Channel::joinChannel(Client& client){
    
    this->addMember(client);
    
    if (this->getMemberNum() == 1){
        this->addOperator(client.getNickname());
    }
}

void Channel::addMember(Client& client){
    this->_memberList.push_back(client);
}

void Channel::addOperator(std::string nickname){
    this->_operatorsList.push_back(nickname);
}

void Channel::setMemberNum(int num){
    this->_memberNum = num;
}

int Channel::getMemberNum(){
    return (this->_memberNum);
}

std::string Channel::getChannelName(){
    return (this->_channelName);
}

bool Channel::isMember(std::string nickname){
    std::list<Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end()){
        if (it->getNickname() == nickname){
            return (true);
        }
        it++;
    }
    return (false);
}