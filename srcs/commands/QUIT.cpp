#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command QUIT
	 * 
	 * @param serv server
	 * @param user user who send request
	 */
	void	QUIT(Server& serv, User& user, Command&) {
		serv.killClient(user);
	}
} // namespace irc
