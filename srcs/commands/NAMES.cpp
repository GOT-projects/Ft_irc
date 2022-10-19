#include "../../includes/includes.hpp"

namespace irc
{
    std::vector<std::string>                channel;
	std::vector<std::string>::iterator      itChan;
	/**
	 * @brief apply command PASS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	NAMES(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() > 1) {
			std::cerr << RED << serv.getLog() << "NAMES: ERR_toomuchPARAMS " << NC << std::endl;
			return;
		}
        // if (cmd.params.size() == 0) {
            for (mapChannelIterator it = serv.getMapChannel().begin(); it != serv.getMapChannel().end(); it++){
                if (!it->second.getMods()._secretFlag && !it->second.getPrivateBool() && !it->second.isInBanList(user.getNickname())){
                    user.sendCommand(RPL_ENDOFNAMES(cmd.params[0]));
                }
                    //std::cerr << "voici la liste des users du channel\n"; // printf list;   RPL_NAMREPLY       RPL_ENDOFNAMES
            }
        // }
        // if (cmd.params.size() == 1) {
        //     channel = split_target(cmd.params[0]);
        //     for (itChan = channel.begin(); itChan != channel.end(); itChan++){
        //         for (mapChannelIterator it = serv.getMapChannel().begin(); it != serv.getMapChannel().end(); it++){
        //             if (!it->second.getMods()._secretFlag && !it->second.getPrivateBool() 
        //             && !it->second.isInBanList(user.getNickname())){
        //                 user.sendCommand(RPL_NAMREPLY(cmd.params[0], "roger"));
        //             }
        //                 //std::cout << "voici la liste des users du channel\n"; // printf list;   RPL_NAMREPLY       RPL_ENDOFNAMES
        //         }
        //     }
        // }
	}
}
