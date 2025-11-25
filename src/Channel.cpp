/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/11/25 17:45:27 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"
#include "../inc/utils.hpp"

Channel::Channel() : _channelName("") {}

Channel::Channel(std::string channelName):_channelName(channelName), _password(""), _topic(""), _memberNum(0), _hasPassword(false), _hasTopic(false){}

Channel::Channel(std::string channelName, std::string password):_channelName(channelName), _password(password), _topic(""), _memberNum(0), _hasPassword(true), _hasTopic(false){}

Channel::~Channel(){}

void Channel::joinChannel(Client& client)
{
    
    this->addMember(client.getNickname(), client);
    
    if (this->getMemberNum() == 1)
    {
        this->addOperator(client.getNickname());
    }
    std::string tosend = "has joined " + this->getChannelName();
    this->sendBroadcast("JOIN", tosend, client);
    // this->sendBroadcast()
}

void Channel::addMember(std::string nickname, Client& client)
{
    this->_memberList[nickname] =  client;
    this->_memberNum++;
}

bool Channel::addOperator(std::string nickname)
{
    Client client;
    
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end()){

        if (it->second.getNickname().compare(nickname) == 0)
        {
            client = it->second;
            this->_memberList.erase(it->first);
            
            this->_memberList["@" + nickname] = client;
            return (true);
        }
        it++;
    }
    return(false);
}

void Channel::setMemberNum(int num)
{
    this->_memberNum = num;
}

int Channel::getMemberNum()
{
    return (this->_memberNum);
}

std::string Channel::getChannelName(){
    return (this->_channelName);
}

bool Channel::isMember(std::string nickname)
{
    std::map<std::string, Client>::iterator it;
    
    it = this->_memberList.find(nickname);
    
    if (it != this->_memberList.end())
    {
        return (true);
    }
    // std::map<Client>::iterator it = this->_memberList.begin();

    // while (it != this->_memberList.end()){
    //     if (it->getNickname() == nickname){
    //         return (true);
    //     }
    //     it++;
    // }
    return (false);
}

bool Channel::hasPassword()
{
    return (this->_hasPassword);
}

bool Channel::hasTopic()
{
    return (this->_hasTopic);
}

void Channel::sendBroadcast(std::string command, std::string tosend, Client& client)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {
        send_irc_reply(it->second, client.userMask(), command, this->getChannelName(), tosend);
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

void  Channel::setTopic(std::string topic)
{
    if (topic.empty())
    {
        this->_topic = topic;
        this->_hasTopic = false;
        return;
    }
    this->_topic = topic;
    this->_hasTopic = true;
}

std::string Channel::getListmember(){
    std::map<std::string, Client>::iterator it = this->_memberList.begin();
    std::string list;
    
    list = it->first;
    it++;
    while(it != this->_memberList.end())
    {
        list.append(" " + it->first);
        it++;
    }
    std::cout << "LIST OF: " << list << std::endl;
    return (list);
}