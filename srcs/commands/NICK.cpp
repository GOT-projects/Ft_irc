#include "../../includes/includes.hpp"

namespace irc
{
	static bool	nicknameValid(const std::string& nick) {
		for (size_t i = 0; i < nick.length(); i++) {
			if (!isalnum(nick[i]))
				return false;
		}
		return true;
	}


	/**
	 * @brief apply command NICK
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	NICK(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			std::cerr << RED << serv.getLog() << "NICK: ERR_NONICKNAMEGIVEN" << NC << std::endl;
			user.sendCommand(ERR_NONICKNAMEGIVEN());
			return ;
		}
		if (!nicknameValid(cmd.params[0])) {
			std::cerr << RED << serv.getLog() << "NICK: ERR_ERRONEUSNICKNAME" << NC << std::endl;
			user.sendCommand(ERR_ERRONEUSNICKNAME(cmd.params[0]));
			return ;
		}
		if (cmd.params[0] == user.getNickname())
			return ;
		User tmp;
		tmp.setNickname(cmd.params[0]).setUsername(user.getUsername());
		if (
			(isInList(tmp, serv.getOnlineUsers(), &isSameNickname) & EXIST_IN_COPY)
			||
			(isInMap(tmp, serv.getWaitingUsers(), &isSameNickname) & EXIST_IN_COPY)
		) {
			std::cerr << RED << serv.getLog() << "NICK: ERR_NICKNAMEINUSE" << NC << std::endl;
			user.sendCommand(ERR_NICKNAMEINUSE(tmp.getNickname()));
			return;
		}
		user.setNickname(cmd.params[0]);
		// Can register
		if (user.isRegister()) {
			// Not already register
			if (isInMap(user, serv.getWaitingUsers(), &isSameUser) == EXIST_IN) {
				// ADD user to online user
				serv.getOnlineUsers().push_back(user);
				// Welcome
				User*	newUser = getUserInList(user, serv.getOnlineUsers(), &isSameUser);
				// RM from anonym users
				serv.getWaitingUsers().erase(getUserIteratorInMap(user, serv.getWaitingUsers(), &isSameUser));
				newUser->sendCommand(RPL_WELCOME(newUser->getNickname()));
				std::cout << serv.getLog() << BLUE_BK << "Users" << NC << BLUE
					<< " In creation: " << serv.getWaitingUsers().size()
					<< " | online: " << serv.getOnlineUsers().size()
					<< NC << std::endl;
			}
		}
	}
} // namespace irc
