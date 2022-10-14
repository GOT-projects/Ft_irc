#include "../../includes/includes.hpp"

namespace irc
{
	void NICK(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			std::cerr << RED << "NICK: too low/many arguments ERR_NONICKNAMEGIVEN" << NC << std::endl;
			// TODO send err
		}
		User tmp;
		tmp.setNickname(cmd.params[0]);
		if (
			(isInList(tmp, serv.getOfflineUsers()) & EXIST_IN_COPY)
			|| (isInList(tmp, serv.getOnlineUsers()) & EXIST_IN_COPY)
			|| (isInMap(tmp, serv.getWaitingUsers()) & EXIST_IN_COPY)
		) {
			std::cerr << RED << "NICK ERR_NICKNAMEINUSE" << NC << std::endl;
			// TODO send error
		}
		user.setNickname(cmd.params[0]);
		//TODO if connected (nick user) go online list
	}
} // namespace irc

