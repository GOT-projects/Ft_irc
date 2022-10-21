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
	void	NAMES(Server& serv, User& user, Command&) {
		for (mapChannelIterator it = serv.getMapChannel().begin(); it != serv.getMapChannel().end(); it++){
			if (!it->second.getMods()._secretFlag && !it->second.getPrivateBool() && !it->second.isInBanList(user.getNickname())){
				user.sendCommand(RPL_NAMREPLY(it->second.getChannelName(), "=", it->second.channelList(), user.getNickname()));
			}
			user.sendCommand(RPL_ENDOFNAMES(it->second.getChannelName(), user.getNickname()));
		}
	}
}