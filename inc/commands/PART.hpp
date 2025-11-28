#ifndef PART_HPP
#define PART_HPP

#include "Command.hpp"

class PART: public Command{
    public:
        PART();
        ~PART();
        void run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args);
};

#endif