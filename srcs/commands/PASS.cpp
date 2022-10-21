#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command PASS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	PASS(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			//std::cout << RED << serv.getLog() << "PASS: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("PASS", ""));
			return;
		}
		if (user.getPass()) {
			//std::cout << RED << serv.getLog() << "PASS: ERR_ALREADYREGISTERED" << NC << std::endl;
			user.sendCommand(ERR_ALREADYREGISTERED());
			return;
		}
		if (cmd.params[0] != serv.getPassword()) {
			//std::cout << RED << serv.getLog() << "PASS: ERR_PASSWDMISMATCH " << NC << std::endl;
			user.sendCommand(ERR_PASSWDMISMATCH());
			return;
		}
		user.setPass(true);
	}
} // namespace irc
