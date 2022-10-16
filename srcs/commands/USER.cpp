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
		Log log;
		if (cmd.params.size() < 4) {
			std::cerr << RED << log << "USER:  ERR_NEEDMOREPARAMS" << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command));
			return;
		}
		if (user.getUsername().size() > 0) {
			std::cerr << log << RED << "USER:  ERR_ALREADYREGISTERED " << NC << std::endl;
			user.sendCommand(ERR_ALREADYREGISTERED());
			return;
		}
		// TODO check is used
		user.setUsername(cmd.params[0]);
		user.setRealname(cmd.params[3]);
		// Can register
		if (canRegisterable(user)) {
			// Not already register
			if (isInMap(user, serv.getWaitingUsers(), &isSameUser) == EXIST_IN) {
				User*	toTransfert = getUserInList(user, serv.getOfflineUsers(), &isSameUsername);
				// If user corresponding to offline user
				if (toTransfert) {
					// ADD offline user update to online state and rm from offline user
					toTransfert->setNickname(user.getNickname()).setSocketFd(user.getSocketFd());
					serv.getOnlineUsers().push_back(*toTransfert);
					serv.getOfflineUsers().erase(getUserIteratorInList(user, serv.getOfflineUsers(), &isSameUsername));
				} else {
					// ADD user to online user
					serv.getOnlineUsers().push_back(user);
				}
				// RM from anonym users
				serv.getWaitingUsers().erase(getUserIteratorInMap(user, serv.getWaitingUsers(), &isSameUser));
			}
		}
	}
} // namespace irc

