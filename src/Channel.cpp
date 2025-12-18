/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvemba <dvemba@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 11:28:28 by dvemba            #+#    #+#             */
/*   Updated: 2025/12/18 10:54:49 by dvemba           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"
#include "../inc/Server.hpp"
#include "../inc/Client.hpp"
#include "../inc/utils.hpp"
#include <sstream>
#include <algorithm>
#include <string>

Channel::Channel() : _channelName(""),
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
                     _topic_time(0)
{}

Channel::Channel(std::string channelName) : _channelName(channelName),
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
                                            _topic_time(0)
{}

// Channel::Channel(std::string channelName, std::string password):_channelName(channelName), _password(password), _topic(""), _topic_by(""), _hasPassword(true), _hasTopic(false), _memberNum(0), _topic_time(0){}

Channel::~Channel() {}

void Channel::joinChannel(Client &client)
{
    if ((this->_limit_mode == false) || 
        (this->_limit_mode == true && static_cast<int>(this->getListmember().size()) <= this->_limit_members) || 
        (this->_limit_members == -1))
    {
        this->addMember(client.getNickname(), client);

        if (this->getMemberNum() == 1)
        {
            this->addOperator(client.getNickname());
        }
        std::string tosend = "has joined " + this->getChannelName();
        this->sendBroadcast("JOIN", tosend, client, true);
    }
    else
        send_irc_reply(client, client.getServername(), ERR_CHANNELISFULL, client.getNickname(), "Channel is full");

// this->sendBroadcast()
}

void Channel::addMember(std::string nickname, Client &client)
{
    this->_memberList[nickname] = client;
    this->_memberNum++;
}

void Channel::removeMember(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {

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

void Channel::sendBroadcastQuit(std::string command, std::string tosend, Client &client, bool isSendSelf)
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

void Channel::sendBroadcast(std::string command, std::string tosend, Client &client, bool isSendSelf)
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

void Channel::setTopic(std::string topic)
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

void Channel::setInvite(Client& client_dest, Client& client_send)
{
    // Client &client_send = this->getClient(client_send.getNickname());
    
    this->addInviteList(client_dest.getNickname());
    std::string dest = client_dest.getNickname() + " " + this->getChannelName();
    send_irc_reply(client_dest, client_send.userMask(), "INVITE", dest, "");
}

bool  Channel::isInvited(std::string nickname)
{
    std::list<std::string>::iterator it = this->_inviteList.begin();

    while (it != this->_inviteList.end())
    {
        if (it->compare(nickname) == 0)
        {
            return (true);
        }
        it++;
    }
    return (false);
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
    if (type_mode == "+t" || type_mode == "-t")
    {
        if (type_mode == "+t" && !this->_topic_mode)
        {
            // std::cout << "Ativou o modo t" << std::endl;
            this->_topic_mode = true;
            // this->_list_modes[type_mode] = "";
            showModes(type_mode.at(0), type_mode.at(1), "");
        }
        else if (type_mode == "-t" && this->_topic_mode)
        {
            // std::cout << "Desativou o modo t" << std::endl;
            this->_topic_mode = false;
            // this->_list_modes[type_mode] = "";
            showModes(type_mode.at(0), type_mode.at(1), "");
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
                // this->_list_modes[type_mode] = (*current_args);
                showModes(type_mode.at(0), type_mode.at(1), (*current_args));
                current_args++;
            }
        }
        else if (type_mode == "-k" && this->_key_mode)
        {
            this->_key_mode = false;
            // this->_list_modes[type_mode] = "";
            showModes(type_mode.at(0), type_mode.at(1), "*");
        }
    }
    if (type_mode == "+l" || type_mode == "-l")
    {
       
        if (type_mode == "+l")
        {
            if (current_args != end_args)
            {
                if (!isStringDigit(*current_args) && std::atoi((*current_args).c_str()) > 0)
                {
                    this->_limit_members = std::atoi((*current_args).c_str());
                    this->_limit_mode = true;
                    // this->_list_modes[type_mode] = (*current_args);
                    showModes(type_mode.at(0), type_mode.at(1), (*current_args));
                }
                current_args++;
            }
        }
        else if (type_mode == "-l" && this->_limit_mode)
        {
            this->_limit_mode = false;
            this->_limit_members = -1;
            showModes(type_mode.at(0), type_mode.at(1), "");
        }
    }
    if (type_mode == "+o" || type_mode == "-o")
    {
       
        if (type_mode == "+o")
        {
            if (current_args != end_args)
            {
                if (this->isMember(*current_args) && !this->isOperator(*current_args))
                {
                    this->addOperator(*current_args);
                    showModes(type_mode.at(0), type_mode.at(1), (*current_args));
                }                    
                current_args++;
            }
        }
        else if (type_mode == "-o" )
        {
            if (current_args != end_args)
            {
                if (this->isMember(*current_args) && this->isOperator(*current_args))
                {
                    this->removeOperator(*current_args);
                    showModes(type_mode.at(0), type_mode.at(1), (*current_args));
                }                    
                current_args++;
            }
        }
    }
    if (type_mode == "+i" || type_mode == "-i")
    {
        if (type_mode == "+i" && !this->_invite_mode)
        {
            std::cout << "Ativou o modo i" << std::endl;
            this->_invite_mode = true;
            // this->_list_modes[type_mode] = "";
            showModes(type_mode.at(0), type_mode.at(1), "");
        }
        else if (type_mode == "-i" && this->_invite_mode)
        {
            std::cout << "Desativou o modo i" << std::endl;
            this->_invite_mode = false;
            // this->_list_modes[type_mode] = "";
            showModes(type_mode.at(0), type_mode.at(1), "");
        }
    }
}
std::string Channel::getModeString(bool showPass)
{
    std::string mode = "+";
    std::string args;
    
    if (this->getInviteMode())
    {
        mode.append("i");
    }
    if (this->getKeyMode())
    {
        mode.append("k");
        args.append(" ");
        if (showPass)
            args.append(this->_password);
        else
           args.append("*"); 
    }
    if (this->getLimitMode())
    {
        mode.append("l");
        std::stringstream ss;
        ss << this->_limit_members;
        args.append(" ");
        args.append(ss.str());
    }
    if (this->getTopicMode())
    {
        mode.append("t");
    }
    return (mode + args);
}
std::string Channel::getCurrentMode()
{
    std::string str;
    std::list<char>::iterator it_mode;
    std::list<std::string>::iterator it_args;

    for (it_mode = _list_mode.begin(); it_mode != _list_mode.end(); it_mode++)
    {
        str.push_back((*it_mode));
    }
    for (it_args = _list_mode_args.begin(); it_args != _list_mode_args.end(); it_args++)
    {
        str.push_back(' ');
        str.append((*it_args));
    }
    _list_mode.clear();
    _list_mode_args.clear();
    return (str);
}
void Channel::showModes(char opt, char mode, std::string args)
{
    std::list<char>::iterator it_mode = _list_mode.begin();

    if (_list_mode.begin() == _list_mode.end())
    {
        _list_mode.push_back(opt);
        _list_mode.push_back(mode);
        if (!args.empty())
        {
            // std::cout << "Tem argumento...." << std::endl;
            _list_mode_args.push_back(args);
        }
        return;
    }
    // for (it_mode != _list_mode.end())
    while (it_mode != _list_mode.end())
    {
        if (opt == (*it_mode))
        {
            // std::list<char>::iterator it = std::find(_list_mode.begin(), _list_mode.end(), opt);
            for (std::list<char>::iterator i = it_mode; i != _list_mode.end(); i++)
            {
                if ((opt == '+' && (*i) == '-') || (opt == '-' && (*i) == '+'))
                {
                    _list_mode.insert(i, mode);  
                    if (!args.empty()){_list_mode_args.push_back(args);}
                    return;
                }
            }
            _list_mode.insert(_list_mode.end(), mode);
            if (!args.empty()){_list_mode_args.push_back(args);}
        }
        else
        {
            std::list<char>::iterator it = std::find(_list_mode.begin(), _list_mode.end(), opt);
            if (it == _list_mode.end())
            {
                _list_mode.push_back(opt);
                _list_mode.push_back(mode);
                if (!args.empty()){_list_mode_args.push_back(args);}
                return;
            }
        }
        it_mode++;
    }
}

Client &Channel::getClient(std::string nickname, Server& server_ref)
{
    return (server_ref.findClient(nickname));
}
bool Channel::isOperator(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {
        if (it->second.getNickname().compare(nickname) == 0)
        {
            if (it->first.compare("@" + nickname) == 0)
            {
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

    while (it != this->_memberList.end())
    {

        if (it->second.getNickname().compare(nickname) == 0)
        {
            client = it->second;
            this->_memberList.erase(it->first);

            this->_memberList["@" + nickname] = client;
            return (true);
        }
        it++;
    }
    return (false);
}

bool Channel::removeOperator(std::string nickname)
{
    Client client;

    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {

        if (it->second.getNickname().compare(nickname) == 0)
        {
            client = it->second;
            this->_memberList.erase(it->first);

            this->_memberList[nickname] = client;
            return (true);
        }
        it++;
    }
    return (false);
}

int Channel::getMemberNum()
{
    return (this->_memberNum);
}

std::string Channel::getChannelName()
{
    return (this->_channelName);
}

bool Channel::isMember(std::string nickname)
{
    std::map<std::string, Client>::iterator it = this->_memberList.begin();

    while (it != this->_memberList.end())
    {
        if (it->second.getNickname() == nickname)
        {
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

    while (it != this->_memberList.end())
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