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
	void	MODE(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			std::cout << RED << serv.getLog() << "PASS: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("PASS"));
			return;
		}
	}
}
