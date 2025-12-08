#include "../../inc/commands/QUIT.hpp"
#include "../../inc/utils.hpp"
#include "../../inc/Channel.hpp"
#include <unistd.h>

QUIT::QUIT(): Command(2){}

QUIT::~QUIT(){}

void QUIT::run_command(Server& server_ref, Client& client_ref, std::vector<std::string> args)
{
    int size_args = args.size();
    std::string target = client_ref.getNickname();

    if (size_args == 0 || size_args > 1)
    {
        try
        {
            std::list<Channel *>::iterator it = server_ref.getListChannel().begin();
            int i = 0;
            while (it != server_ref.getListChannel().end())
            {
                Channel* channel = *it;

                if (channel->isMember(client_ref.getNickname()))
                {
                    std::string tosend = "has quit " + channel->getChannelName();
                    // send_irc_reply(client_ref, client_ref.userMask(), "QUIT", channel.getChannelName(), tosend);
                    channel->sendBroadcast("QUIT", "Client quit", client_ref, true);
                    channel->removeMember(client_ref.getNickname());
                    if (channel->getListmember().empty())
                    {
                        server_ref.removeChannel(channel->getChannelName());
                    }
                    if (i == 0)
                    {
                        i = 1;
                        close(client_ref.get_fd());
                    }
                }
                it++;
            }
            
            
        }
        catch(const std::exception& e)
        {
            send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
            return;
        }
    }

    // if (size_args > 0 && )
    // {
    //     std::cout << args[1].at(0) << std::endl;
    //     try
    //     {
    //         Channel& channel = server_ref.findChannel(args[0]);
    //         if (!channel.isMember(client_ref.getNickname()))
    //         {
    //             send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOTONCHANNEL, target + " " + channel.getChannelName(), "You're not on that channel");
    //             return;
    //         }
    //         std::string tosend = "has quit " + channel.getChannelName();
    //         // send_irc_reply(client_ref, client_ref.userMask(), "QUIT", channel.getChannelName(), tosend);
    //         channel.sendBroadcast("QUIT", args[1], client_ref, true);
    //         channel.removeMember(client_ref.getNickname());
    //         if (channel.getListmember().empty())
    //         {
    //             server_ref.removeChannel(channel.getChannelName());
    //         }
            
    //     }
    //     catch(const std::exception& e)
    //     {
    //         send_irc_reply(client_ref, server_ref.get_Servername(), ERR_NOSUCHCHANNEL, target + " " + args[0], "No such channel");
    //         return;
    //     }
    // }
    
    
    
}