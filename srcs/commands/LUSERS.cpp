#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command LUSERS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	LUSERS(Server& serv, User& user, Command& ) {
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "LUSERS: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}else if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "LUSERS: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
        }
    };
}//namespace irc
