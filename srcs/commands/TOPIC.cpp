#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command TOPIC
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	TOPIC(Server& serv, User& user, Command& cmd) {
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "TOPIC: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}
		if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "TOPIC: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
		}else if (cmd.params.size() < 1){
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, "add channel"));
		}else if (cmd.params.size() == 1){
			mapChannelIterator it = serv.getMapChannel().begin();
			for(; it != serv.getMapChannel().end(); ++it){
				if (it->first == cmd.params[0]){
					if (it->second.getChannelTopic() == "")
						user.sendCommand(RPL_NOTOPIC(cmd.params[0]));
					else{
						user.sendCommand(RPL_TOPIC(cmd.params[0], it->second.getChannelTopic()));
						user.sendCommand(RPL_TOPICWHOTIME(cmd.params[0], user.getNickname(), serv.getLog().getTime()));
					}
				}
			}
			user.sendCommand(ERR_NOSUCHSERVER(cmd.params[0]));
		}else if (cmd.params.size() == 2){
			mapChannelIterator it = serv.getMapChannel().begin();
			for(; it != serv.getMapChannel().end(); ++it){
				//TODO function add topic in channel nut maybe need check if oper for know if the user can do or not
				if (it->first == cmd.params[0]){
					it->second.changeChanTopic(cmd.params[1]);
				}
			}
		}
		/* TODO rcuminal
		if (cmd.params.size() < 1) {
			std::cout << RED << serv.getLog() << "PASS: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("PASS"));
			return;
		}
		if (cmd.params.size() > 2) {
			std::cout << RED << serv.getLog() << "PASS: TOOMANYPARAMS " << NC << std::endl;

			return;
		}
		if (cmd.params[0][0] == '#' || cmd.params[0][0] == '&'){
			mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
			if (cmd.params.size() == 2){
				std::cout << "envoyer de topic : " << it->second.getChannelTopic() << std::endl;
			}
			else {
				if (it->second.getMods()._topicFlag){
					if (it->second.isInOperatorList(user.getNickname()))
						it->second.changeChanTopic(cmd.params[1]);
					else {
						std::cerr << "ERR_NOTOPERATOR\n";
					}
				}
				else {
					it->second.changeChanTopic(cmd.params[1]);
				}
			}
		}
		*/
	};
}//namespace irc
