#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command VERSION
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	VERSION(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() == 0){
			std::cerr << RED << serv.getLog() << "VERSION: Error to many param receive" << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, "add server name"));
			return;
		}else if(cmd.params[0] == "ft_irc" || cmd.params[0] == "irc"){
			user.sendCommand(RPL_VERSION("v1.0.0", "ft_irc v1.0.0", "Project 42"));
			return;
		}else{
			user.sendCommand(ERR_NOSUCHSERVER(cmd.params[0]));
		}
	};
}//namespace irc
