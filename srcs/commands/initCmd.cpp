#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief static member function of Server class which construct
	 * the map of commands
	 * 
	 * @return mapCommand a map <commandName - functionCommand>
	 */
	mapCommand	Server::initCmd(void){
		mapCommand	ret;
		ret["MODE"] = &MODE;
		ret["PRIVMSG"] = &PRIVMSG;
		ret["NICK"] = &NICK;
		ret["PASS"] = &PASS;
		ret["PING"] = &ping;
		ret["PONG"] = &pong;
		ret["JOIN"] = &JOIN;
		ret["TOPIC"] = &TOPIC;
		ret["NAMES"] = &NAMES;
		ret["USER"] = &USER;
		ret["CAP"] = &CAP;
		ret["KICK"] = &KICK;
		ret["INFO"] = &INFO;
		ret["NOTICE"] = &NOTICE;
		ret["KILL"] = &KILL;
		ret["HELP"] = &HELP;
		ret["PART"] = &PART;
		ret["VERSION"] = &VERSION;
		ret["LUSERS"] = &LUSERS;
		ret["TIME"] = &TIME;
		ret["QUIT"] = &QUIT;
		ret["OPER"] = &OPER;
		ret["INVITE"] = &INVITE;
		return ret;
	}

	/**
	 * @brief Check if the user can receive command for registration
	 * If not the error will be print on cerr
	 * 
	 * @param user the user
	 * @param cmd the command name
	 * @param serv the server
	 * @return true if the user can receive command for register, else false
	 */
	bool	canRegister(const User& user, const std::string& cmd, Server& serv) {
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << cmd << ": Cap error"
				<< NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return false;
		}
		if (!user.getPass()) {
			std::cerr << RED << serv.getLog() << cmd << ": password required"
				<< NC << std::endl;
			user.sendCommand(":please set password");
			return false;
		}
		return true;
	}

	bool	canExecute(Server& serv, const User& user, const std::string& cmd) {
		if (cmd != "CAP") {
			if (!user.getCap()) {
				std::cerr << RED << serv.getLog() << cmd << ": Cap error"
					<< NC << std::endl;
				user.sendCommand(":please set cap to 302");
				return false;
			}
			if (cmd != "PASS") {
				if (!user.getPass()) {
					std::cerr << RED << serv.getLog() << cmd << ": password required"
						<< NC << std::endl;
					user.sendCommand(":please set password");
					return false;
				}
				// if not command not need registration
				if (cmd != "USER" && cmd != "NICK" && cmd != "HELP" && cmd != "INFO" && cmd != "QUIT" && cmd != "TIME") {
					if (!user.isRegister()) {
						std::cerr << RED << serv.getLog() << cmd << ": need to be register"
							<< NC << std::endl;
						user.sendCommand(":please register USER / NICK");
						return false;
					}
				}
			}
		}
		return true;
	}

} // namespace irc
