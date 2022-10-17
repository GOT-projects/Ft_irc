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
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "PING: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}
		if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "PING: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
		}
		if (user.getUsername() == "" || user.getNickname() == "")
			return;
		if (cmd.params.size() < 1){
			std::cerr << RED << serv.getLog() << "PING: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS());
			return;
		}
		user.sendCommand(PONG(cmd.params[0]));
	};
}//namespace irc
