#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command KILL
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	KILL(Server& serv, User& user, Command& cmd) {
		if (!user.isOperatorServer()) {
			std::cerr << RED << serv.getLog() << "KILL: ERR_NOPRIVILEGES " << NC << std::endl;
			user.sendCommand(ERR_NOPRIVILEGES(user));
			return;
		}
		if (cmd.params.size() < 2){
			std::cerr << RED << serv.getLog() << "KILL: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
		User tmp;
		tmp.setNickname(cmd.params[0]);
		User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
		if (userSend != NULL) {
			userSend->sendCommand(S_NOTICE(user, cmd.params[0], cmd.params[1]));
			serv.killClient(*userSend);
		}
		else
			user.sendCommand(ERR_NOSUCHNICK(user, cmd.params[0]));
	}
} // namespace irc
