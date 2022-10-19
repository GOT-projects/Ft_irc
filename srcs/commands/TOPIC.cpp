
#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command PING
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	TOPIC(Server& serv, User& user, Command&) {
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
			if (!cmd.params[1]){
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
	};
}//namespace irc
