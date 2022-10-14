#include "../../includes/includes.hpp"

namespace irc
{
	void USER(Server& serv, User& user, Command& cmd) {
		serv.getOnlineUsers();
		if (cmd.params.size() < 4) {
			std::cerr << RED << "USER:  ERR_NEEDMOREPARAMS" << NC << std::endl;
			user.sendCommand("USER :Not enough parameters\r\n"); //FIXME
		}
		else if (user.getUsername().size() > 0) {
			std::cerr << RED << "USER:  ERR_ALREADYREGISTERED " << NC << std::endl;
			user.sendCommand("USER :You may not reregister\r\n");//FIXME
		}else {
			user.setUsername(cmd.params[0]);
			user.setRealname(cmd.params[3]);
		}
		//TODO if connected (nick user) go online list
	}
} // namespace irc

