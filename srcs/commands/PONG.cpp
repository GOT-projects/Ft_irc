
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
	void	pong(Server& serv, User& user, Command&) {
		if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "PING: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
		}
	};

}//namespace irc
