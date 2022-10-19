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
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "TIME: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}else if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "TIME: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
		}else if (cmd.params.size() == 0){
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
