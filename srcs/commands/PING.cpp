
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
	void	ping(Server& , User& user, Command& cmd) {
		Log log;
		if (cmd.params.size() == 0){
			std::cerr << RED << log << "USER: ERR_NOORIGIN" << NC << std::endl;
			user.sendCommand(ERR_NOORIGIN());
		}else if (cmd.params.size() >= 1){
			user.sendCommand(PONG(cmd.params[0]));
		} 
	};
}//namespace irc
