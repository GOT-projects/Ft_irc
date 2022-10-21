#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command TIME
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	TIME(Server& serv, User& user, Command& cmd) {
		Log log;
		if (cmd.params.size() == 0){
			std::cerr << RED << serv.getLog() << "TIME: Error to many param receive" << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, "add server name"));
			return;
		}else if(cmd.params[0] == "ft_irc" || cmd.params[0] == "irc"){
			user.sendCommand(RPL_TIME(cmd.params[0], log.getTime()));
			return;
		}else{
			user.sendCommand(ERR_NOSUCHSERVER(cmd.params[0]));
		}
	};
}//namespace irc
