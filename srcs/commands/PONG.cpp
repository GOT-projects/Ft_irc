
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
	void	pong(Server&, User& user, Command& cmd) {
		user.sendCommand(PING(cmd.params[0]));
	};

}//namespace irc
