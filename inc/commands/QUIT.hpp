#ifndef QUIT_HPP
#define QUIT_HPP

#include "Command.hpp"

class QUIT: public Command{
    public:
        QUIT();
        ~QUIT();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif