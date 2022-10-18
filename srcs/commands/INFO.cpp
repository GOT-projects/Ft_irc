
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
	void	INFO(Server& serv, User& user, Command&) {
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "INFO: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}
		if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "INFO: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
		}
		user.sendCommand(RPL_INFO("Irc Server:"));
		user.sendCommand(RPL_INFO("Project 42"));
		user.sendCommand(RPL_INFO("Create by:"));
		user.sendCommand(RPL_INFO("          Aartige"));
		user.sendCommand(RPL_INFO("          Rcuminal"));
		user.sendCommand(RPL_INFO("          Jmilhas"));
		user.sendCommand(RPL_ENDOFINFO());
	};
}//namespace irc
