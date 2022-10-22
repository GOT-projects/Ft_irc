#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command INFO
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	PART(Server& serv, User& user, Command& cmd) {
		
        
            mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
            if (it->second.isInChannel(user.getNickname())){
                user.sendCommand(S_PART(user.getNickname(), it->second.getChannelName()));
                it->second.kick(user);
            }
		
	};
}