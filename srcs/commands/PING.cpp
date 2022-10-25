#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command PING
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	ping(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1){
			std::cerr << RED << serv.getLog() << "PING: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("PING", ""));
			return;
		}
		user.sendCommand(PONG(cmd.params[0]));
	};
}//namespace irc
