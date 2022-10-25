#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command INFO
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	INFO(Server&, User& user, Command&) {
		user.sendCommand(RPL_INFO("Irc Server:"));
		user.sendCommand(RPL_INFO("Project 42"));
		user.sendCommand(RPL_INFO("Create by:"));
		user.sendCommand(RPL_INFO(":          Aartiges"));
		user.sendCommand(RPL_INFO(":          Rcuminal"));
		user.sendCommand(RPL_INFO(":          Jmilhas"));
		user.sendCommand(RPL_ENDOFINFO());
	};
}//namespace irc
