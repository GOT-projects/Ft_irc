#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command OPER
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	OPER(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 2){
			std::cerr << RED << serv.getLog() << "OPER: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
		User tmp;
		tmp.setNickname(cmd.params[0]);
		User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
		if (userSend != NULL) {
			if (cmd.params[1] == serv.getOperPassword()) {
				userSend->beOperatorServer(true);
				userSend->sendCommand(RPL_YOUREOPER());
			}
			else
				userSend->sendCommand(ERR_PASSWDMISMATCH());
		}
		else
			user.sendCommand(ERR_NOOPERHOST(user.getNickname()));
	}
} // namespace irc
