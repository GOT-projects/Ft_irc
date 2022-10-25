#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command TOPIC
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	TOPIC(Server& serv, User& user, Command& cmd) {
		if (cmd.params[0][0] == '#' || cmd.params[0][0] == '&'){
			if (cmd.params.size() < 1){
				user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, "add channel"));
			}else if (cmd.params.size() == 1){
				mapChannelIterator it = serv.getMapChannel().begin();
				for(; it != serv.getMapChannel().end(); ++it){
					if (it->first == cmd.params[0]){
						if (it->second.getChannelTopic() == "")
							user.sendCommand(RPL_NOTOPIC(cmd.params[0]));
						else{
							user.sendCommand(RPL_TOPIC(cmd.params[0], it->second.getChannelTopic()));
							user.sendCommand(RPL_TOPICWHOTIME(cmd.params[0], user.getNickname(), serv.getLog().getTime()));
						}
						return ;
					}
				}
				user.sendCommand(ERR_NOSUCHSERVER(cmd.params[0]));
			}else if (cmd.params.size() == 2){
				mapChannelIterator it = serv.getMapChannel().begin();
				for(; it != serv.getMapChannel().end(); ++it){
					if (it->first == cmd.params[0]){
						if (it->second.getMods()._topicFlag){
							if (it->second.isInOperatorList(user.getNickname()))
								it->second.changeChanTopic(cmd.params[1]);
							else
								user.sendCommand(ERR_CHANOPRIVSNEEDED(cmd.params[0]));
						}
						else
							it->second.changeChanTopic(cmd.params[1]);
						return ;
					}
				}
				user.sendCommand(ERR_NOSUCHSERVER(cmd.params[0]));
			}
		}
	};
}
