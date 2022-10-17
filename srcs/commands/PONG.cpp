
#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command PONG
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	pong(Server& serv, User& user, Command& cmd) {
		if (!canExecute(user, cmd.command, serv))
			return;
	};

}//namespace irc
