/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/20 17:49:47 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"

Channel::Channel(std::string channelName):_channelName(channelName){}

Channel::~Channel(){}

void Channel::joinChannel(std::string nickname){
    
    this->addMember(nickname);
    
    if (this->getMemberNum() == 1){
        this->addOperator(nickname);
    }
}

void Channel::addMember(std::string& nickname){
    this->_memberList.push_back(nickname);
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
    std::list<std::string>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end()){
        if (it->compare(nickname) == 0){
            return (true);
        }
        it++;
    }
    return (false);
}