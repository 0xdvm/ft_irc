#ifndef INVITE_HPP
#define INVITE_HPP

#include "Command.hpp"
class Channel;

class INVITE: public Command{
    public:
        INVITE();
        ~INVITE();
        void                run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif