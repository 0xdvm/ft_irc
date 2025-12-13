/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/13 21:30:08 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"
#include "../inc/utils.hpp"
#include <sstream>

Channel::Channel() : 
            _channelName(""), 
            _password(""), 
            _topic(""), 
            _topic_by(""), 
            
            _topic_mode(false),
            _invite_mode(false),
            _key_mode(false),
            _limit_mode(false), 
            
            _hasPassword(false), 
            _hasTopic(false), 
            _memberNum(0), 
            _topic_time(0) {}

Channel::Channel(std::string channelName):
            _channelName(channelName), 
            _password(""), 
            _topic(""), 
            _topic_by(""),
            
            _topic_mode(false),
            _invite_mode(false),
            _key_mode(false),
            _limit_mode(false), 
            
            // _hasPassword(false), 
            _hasTopic(false), 
            _memberNum(0), 
            _topic_time(0){}

// Channel::Channel(std::string channelName, std::string password):_channelName(channelName), _password(password), _topic(""), _topic_by(""), _hasPassword(true), _hasTopic(false), _memberNum(0), _topic_time(0){}

Channel::~Channel(){}

void Channel::joinChannel(Client& client)
{
    
    this->addMember(client.getNickname(), client);
    
    if (this->getMemberNum() == 1)
    {
        this->addOperator(client.getNickname());
    }
    std::string tosend = "has joined " + this->getChannelName();
    this->sendBroadcast("JOIN", tosend, client, true);
    // this->sendBroadcast()
}

void Channel::addMember(std::string nickname, Client& client)
{
    this->_memberList[nickname] =  client;
    this->_memberNum++;
}

void Channel::removeMember(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end()){

        if (it->second.getNickname().compare(nickname) == 0)
        {
            this->_memberList.erase(it->first);
            return;
        }
        it++;
    }
}

void Channel::setMemberNum(int num)
{
    this->_memberNum = num;
}

void Channel::sendBroadcastQuit(std::string command, std::string tosend, Client& client, bool isSendSelf)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {
        if ((it->second.getNickname().compare(client.getNickname()) != 0 || isSendSelf))
        {
            send_irc_reply(it->second, client.userMask(), command, "", tosend);
        }
        it++;
    }
}

void Channel::sendBroadcast(std::string command, std::string tosend, Client& client, bool isSendSelf)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {
        if ((it->second.getNickname().compare(client.getNickname()) != 0 || isSendSelf))
        {
            send_irc_reply(it->second, client.userMask(), command, this->getChannelName(), tosend);
        }
        it++;
    }
}

void  Channel::setTopic(std::string topic)
{
    if (topic.compare(":") == 0)
    {
        this->_topic = "";
        this->_hasTopic = false;
    }
    else
    {
        this->_topic = topic;
        this->_hasTopic = true;
    }
}

void Channel::addInviteList(std::string nickname)
{
    this->_inviteList.push_back(nickname);
}

void Channel::removeInviteList(std::string nickname)
{
    std::list<std::string>::iterator it = this->_inviteList.begin();

    while (it != this->_inviteList.end())
    {
        if (it->compare(nickname) == 0)
        {
            this->_inviteList.erase(it);
            break;
        }
        it++;
    }
}

void Channel::setInvite(std::string nickname, std::string nickaname_dest)
{
    Client &client_dest = this->getClient(nickaname_dest);
    Client & client_send = this->getClient(nickname);
    if (this->isOperator(nickname))
    {
        this->addInviteList(nickaname_dest);
        send_irc_reply(client_dest, nickname, client_send.userMask(), "INVITE", this->_channelName);
    }
    else
    {
        send_irc_reply(client_send, client_send.getServername(), ERR_CHANOPRIVSNEEDED, client_send.getNickname(), "You're not channel operator");
    }
}
void Channel::setTopicby(std::string nick)
{
    this->_topic_by = nick; 
}

void Channel::setTopicTime(long int time)
{
    this->_topic_time = time;
}
void Channel::executeMode(std::string type_mode, std::vector<std::string>::iterator &current_args, std::vector<std::string>::iterator end_args)
{
    (void)current_args;
    (void)end_args;
    
    if (type_mode == "+t" || type_mode == "-t")
    {
        if (type_mode == "+t" && !this->_topic_mode)
        {
            std::cout << "Ativou o modo" << std::endl;
            this->_topic_mode = true;
            this->_list_modes[type_mode] = "";
        }
        else if (type_mode == "-t" && this->_topic_mode)
        {
            this->_topic_mode = false;
            this->_list_modes[type_mode] = "";
        }
    }
    if (type_mode == "+k" || type_mode == "-k")
    {
        if (type_mode == "+k")
        {
            if (current_args != end_args)
            {
                this->_password = (*current_args);
                this->_key_mode = true;
                this->_list_modes[type_mode] = (*current_args);
                current_args++;
            }
        }
        else if (type_mode == "-k" && this->_key_mode)
        {
            this->_key_mode = false;
            this->_list_modes[type_mode] = "";
        }
    }
}
void Channel::showModes()
{
    std::string list_modes;
    std::string list_args;
    int signal = 0;

    std::map<std::string, std::string>::iterator it = this->_list_modes.begin();
    while (it != this->_list_modes.end())
    {
        std::cout << "mode: " << (*it).first.at(1) << std::endl;
        if ((*it).first.at(0) == '+')
        {
            if (signal == 0)
            {
                list_modes.append("+");
                signal = 1;
            }
           list_modes.push_back((*it).first.at(1));
        }
        list_args.append(" ");
        list_args += (*it).second;
        it++;
    }
    signal = 0;
    it = this->_list_modes.begin();
    while (it != this->_list_modes.end())
    {
        if ((*it).first.at(0) == '-')
        {
            if (signal == 0)
            {
                list_modes.append("-");
                signal = 1;
            }
            
           list_modes.push_back((*it).first.at(1));
        }
        it++;
    }
    std::cout << list_modes << list_args << std::endl;
}

Client& Channel::getClient(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {
        if (it->second.getNickname().compare(nickname) == 0)
        {
            return (it->second);
        }
        it++;
    }
    throw std::runtime_error("User not found");
}

bool Channel::isOperator(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();
    
    while (it != this->_memberList.end())
    {
        if (it->second.getNickname().compare(nickname) == 0)
        {
            if (it->first.compare("@" + nickname) == 0){
                return (true);
            }
        }
        it++;
    }
    return (false);
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

int Channel::getMemberNum()
{
    return (this->_memberNum);
}

std::string Channel::getChannelName(){
    return (this->_channelName);
}

bool Channel::isMember(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();
    
    // it = this->_memberList.find(nickname);
    
    // if (it != this->_memberList.end())
    // {
    //     return (true);
    // }
    // std::map<Client>::iterator it = this->_memberList.begin();
    
    while (it != this->_memberList.end()){
    if (it->second.getNickname() == nickname){
            return (true);
        }
        it++;
    }
    return (false);
}
        
bool Channel::hasTopic()
{
    return (this->_hasTopic);
}

bool Channel::isCorrectpassword(std::string password)
{
    if (this->_password.compare(password) == 0)
    {
        return (true);
    }
    return (false);
}
bool Channel::getTopicMode()
{
    return (this->_topic_mode);
}
bool Channel::getInviteMode()
{
    return (this->_invite_mode);
}
bool Channel::getKeyMode()
{
    return (this->_key_mode);
}
bool Channel::getLimitMode()
{
    return (this->_limit_mode);
}


std::string Channel::getListmember()
{
    if (this->_memberList.empty())
        return std::string();
    
    std::map<std::string, Client>::iterator it = this->_memberList.begin();
    std::string list;
    
    while(it != this->_memberList.end())
    {
        if (it != this->_memberList.begin())
            list.push_back(' ');
        list += it->first;
        it++;
    }
    std::cout << "LIST OF: " << list << std::endl;
    return (list);
}

std::string Channel::getTopic()
{
    return (this->_topic);
}

std::string Channel::getTopicby()
{
    return (this->_topic_by);
}

std::string Channel::getTopicTime()
{
    std::stringstream ss;
    ss << this->_topic_time;
    return (ss.str());
}