#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command USER
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	USER(Server& serv, User& user, Command& cmd) {
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "USER: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}

		if (!user.getPass()) {
			std::cerr << RED << serv.getLog() << "USER: password required" << NC << std::endl;
			user.sendCommand(":please set password");
			return;
		}
		// TODO test if pass
		if (cmd.params.size() < 4) {
			std::cerr << RED << serv.getLog() << "USER: ERR_NEEDMOREPARAMS" << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command));
			return;
		}
		if (user.getUsername().size() > 0) {
			std::cerr << serv.getLog() << RED << "USER: ERR_ALREADYREGISTERED " << NC << std::endl;
			user.sendCommand(ERR_ALREADYREGISTERED());
			return;
		}
		// TODO check is used [unique] quelle erreur
		user.setUsername(cmd.params[0]);
		user.setRealname(cmd.params[3]);
		// Can register
		if (isRegister(user)) {
			// Not already register
			if (isInMap(user, serv.getWaitingUsers(), &isSameUser) == EXIST_IN) {
				// ADD user to online user
				serv.getOnlineUsers().push_back(user);
				// RM from anonym users
				serv.getWaitingUsers().erase(getUserIteratorInMap(user, serv.getWaitingUsers(), &isSameUser));
				// Welcome
				User*	newUser = getUserInList(user, serv.getOnlineUsers(), &isSameUser);
				newUser->sendCommand(RPL_WELCOME(user.getNickname()));
			}
		}
	}
} // namespace irc
