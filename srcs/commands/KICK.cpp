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
	void	KICK(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 2) {
			//std::cout << RED << serv.getLog() << "MODE: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
        if (cmd.params.size() == 2) {
            mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
            if (it->second.isInChannel(cmd.params[1]) && it->second.isInOperatorList(user.getNickname()))
                user.sendCommand(S_KICK(user.getNickname(), it->second.getChannelName(), cmd.params[1]));
		}
	};
}
