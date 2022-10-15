#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command USER
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	USER(Server& serv, User& user, Command& cmd) {
		Log log;
		serv.getOnlineUsers();
		if (cmd.params.size() < 4) {
			std::cerr << RED << log << "USER:  ERR_NEEDMOREPARAMS" << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command));
		}
		else if (user.getUsername().size() > 0) {
			std::cerr << log << RED << "USER:  ERR_ALREADYREGISTERED " << NC << std::endl;
			user.sendCommand(ERR_ALREADYREGISTERED());
		}else {
			user.setUsername(cmd.params[0]);
			user.setRealname(cmd.params[3]);
		}
		//TODO if connected (nick user) go online list
	}
} // namespace irc

