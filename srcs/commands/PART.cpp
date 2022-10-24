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
		std::vector<std::string>                channel;
		std::vector<std::string>::iterator      itChan;

		if (cmd.params.size() == 0){
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}

		channel = split_target(cmd.params[0], ',', true);
		for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
			if ((*itChan)[0] == '#' || (*itChan)[0] == '&'){
        		mapChannelIterator it = serv.getMapChannel().find(*itChan);
				if (it == serv.getMapChannel().end())
					user.sendCommand(ERR_NOSUCHCHANNEL(*itChan));
        		else if (it->second.isInChannel(user.getNickname())){
        		    it->second.sendMessage(S_PART(user, it->second.getChannelName()));
        		    if (it->second.kick(user) == 2)
						serv.getMapChannel().erase(it);
        		}
				else
					user.sendCommand(ERR_NOTONCHANNEL(user.getNickname(), *itChan));
			}
		}
	
	};
}