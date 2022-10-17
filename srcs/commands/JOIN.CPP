#include "../../includes/includes.hpp"

namespace irc
{
    void	JOIN(Server& serv, User& user, Command& cmd) {
        std::vector<std::string>                channel;
        std::vector<std::string>                key;
        std::vector<std::string>::iterator      itChan;
        if (cmd.params.size() < 1){
            std::cout << "ERR_NEEDMOREPARAMS\n"; 
            return;
        }
        //split params[0] if have ',' for open multi channel
        //TODO need use target for go or home new channel 
        //and need check target[0] = '#' || '&' || '@' for change the oper of the channel
        //TODO for test use cmd:   \join #test,#tes1,#tes2,&test3
        //Example list
        //              JOIN #foobar                    ; join channel #foobar.  @Handle
        //              JOIN &foo fubar                 ; join channel &foo using key "fubar".
        //              JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
        //                                              and &bar using no key.
        //              
        //              JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
        //                                              and channel #bar using key "foobar".
        //              
        //              JOIN #foo,#bar                  ; join channels #foo and #bar.  @handle
        //              
        channel = split_target(cmd.params[0]);
        if (channel.size() > CHANNEL_MAX){
            user.sendCommand(ERR_TOOMANYCHANNELS());
            return;
        }
        if (cmd.params.size() == 1){
            std::cout << "Channel: \n";
            for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
                std::cout << "\n\t\t chan " << *itChan << std::endl;
                if (serv.isInMapChannel(*itChan)){
                    mapChannelIterator it = serv.getMapChannel().find(*itChan);
                    it->second.joinChannel(user);
                    it->second.sendMessage(S_JOIN(user, *itChan));
                }else {
                    Channel chan = Channel(*itChan);
                    serv.getMapChannel().insert(std::pair<std::string, Channel>(*itChan, chan));
                    mapChannelIterator it = serv.getMapChannel().find(*itChan);
                    it->second.joinChannel(user);
                    it->second.sendMessage(S_JOIN(user, *itChan));
                }
            }
        }else if (cmd.params.size() == 2){
            key = split_target(cmd.params[1]);
            //TODO need for same but with key 
        }
    }

    // void	QUIT(Server& serv, User& user, Command& cmd) {
    //     if (cmd.params.size() < 1){
    //         std::cout << "ERR_NEEDMOREPARAMS\n"; 
    //         return;
    //     }
    //     // check des channel dans le tableau de channel
    //     if (serv.isInMapChannel(cmd.params[0]))
    //     {
    //         mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
    //         it->second.joinChannel(user);
    //         it->second.sendMessage(S_JOIN(user, cmd.params[0]));
    //     }
    //     else {
    //         Channel chan = Channel(cmd.params[0]);
    //         serv.getMapChannel().insert(std::pair<std::string, Channel>(cmd.params[0], chan));
    //         mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
    //         it->second.joinChannel(user);
    //         it->second.sendMessage(S_JOIN(user, cmd.params[0]));
            
    //         //message a renvoyé
    //     }
    // }
}
