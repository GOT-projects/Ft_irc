#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command NICK
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	NICK(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			std::cerr << RED << "NICK: too low/many arguments ERR_NONICKNAMEGIVEN" << NC << std::endl;
			// TODO send err
			return ;
		}
		if (cmd.params[0] == user.getNickname())
			return ;
		User tmp;
		tmp.setNickname(cmd.params[0]).setUsername(user.getUsername());
		if (
			(isInList(tmp, serv.getOnlineUsers(), &isSameNickname) & EXIST_IN_COPY)
			|| (isInMap(tmp, serv.getWaitingUsers(), &isSameNickname) & EXIST_IN_COPY)
		) {
			std::cerr << RED << "NICK ERR_NICKNAMEINUSE" << NC << std::endl;
			user.sendCommand(ERR_NICKNAMEINUSE(tmp.getNickname()));
			return;
		}
		user.setNickname(cmd.params[0]);
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
