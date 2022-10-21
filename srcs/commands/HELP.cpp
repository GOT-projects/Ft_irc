#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command HELP
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	HELP(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() != 0){
			std::cerr << RED << serv.getLog() << "HELP: Error to many param receive" << NC << std::endl;
			user.sendCommand(ERR_HELPNOTFOUND(cmd.params[0]));
			return;
		}
		user.sendCommand(RPL_HELPSTART("List of command"));
		user.sendCommand(RPL_HELPTXT("USER"));
		user.sendCommand(RPL_HELPTXT("NICK"));
		user.sendCommand(RPL_HELPTXT("VERSION"));
		user.sendCommand(RPL_HELPTXT("LUSERS"));
		user.sendCommand(RPL_HELPTXT("INFO"));
		user.sendCommand(RPL_HELPTXT("MODE"));
		user.sendCommand(RPL_HELPTXT("PRIVMSG"));
		user.sendCommand(RPL_HELPTXT("NOTICE"));
		user.sendCommand(RPL_HELPTXT("PING"));
		user.sendCommand(RPL_HELPTXT("PONG"));
		user.sendCommand(RPL_HELPTXT("JOIN"));
		user.sendCommand(RPL_HELPTXT("QUIT"));
		user.sendCommand(RPL_HELPTXT("OPER"));
		user.sendCommand(RPL_HELPTXT("PART"));
		user.sendCommand(RPL_HELPTXT("TOPIC"));
		user.sendCommand(RPL_HELPTXT("NAMES"));
		user.sendCommand(RPL_HELPTXT("LIST"));
		user.sendCommand(RPL_HELPTXT("INVITE"));
		user.sendCommand(RPL_HELPTXT("KICK"));
		user.sendCommand(RPL_ENDOFHELP("HELP"));
	};
}//namespace irc
