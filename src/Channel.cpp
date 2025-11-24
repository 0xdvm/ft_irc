/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/24 21:08:30 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"
#include "../inc/utils.hpp"

Channel::Channel() : _channelName("") {}

Channel::Channel(std::string channelName):_channelName(channelName), _password(""), _topic(""), _memberNum(0), _hasPassword(false){}

Channel::Channel(std::string channelName, std::string password):_channelName(channelName), _password(password), _topic(""), _memberNum(0), _hasPassword(true){}

Channel::~Channel(){}

void Channel::joinChannel(Client& client){
    
    this->addMember(client);
    
    if (this->getMemberNum() == 1){
        this->addOperator(client.getNickname());
    }
    std::string tosend = "has joined " + this->getChannelName();
    this->sendBroadcast("JOIN", tosend, client);
}

void Channel::addMember(Client& client){
    this->_memberList.push_back(client);
    this->_memberNum++;
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

bool Channel::hasPassword()
{
    return (this->_hasPassword);
}

void Channel::sendBroadcast(std::string command, std::string tosend, Client& client)
{
    std::list<Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end()){
        send_irc_reply(*it, client.userMask(), command, this->getChannelName(), tosend);
        it++;
    }
}

bool Channel::isCorrectpassword(std::string password)
{
    if (this->_password.compare(password) == 0)
    {
        return (true);
    }
    return (false);
}