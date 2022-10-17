#include "../../includes/includes.hpp"

namespace irc
{
    void	JOIN(Server& serv, User& user, Command& cmd) {
        if (cmd.params.size() < 1){
            std::cout << "ERR_NEEDMOREPARAMS\n"; 
            return;
        }
        // check des channel dans le tableau de channel
        if (serv.isInMapChannel(cmd.params[0]))
        {
            mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
            it->second.joinChannel(user);
            it->second.sendMessage(S_JOIN(user, cmd.params[0]));
        }
        else {
            Channel chan = Channel(cmd.params[0]);
            serv.getMapChannel().insert(std::pair<std::string, Channel>(cmd.params[0], chan));
            mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
            it->second.joinChannel(user);
            it->second.sendMessage(S_JOIN(user, cmd.params[0]));
            
            //message a renvoyé
        }
    }
}