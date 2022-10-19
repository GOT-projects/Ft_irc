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
                    if (it->second.getTopic() == "")
                        user.sendCommand(RPL_NOTOPIC(cmd.params[0]));
                    else{
                        user.sendCommand(RPL_TOPIC(cmd.params[0], it->second.getTopic()));
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
	};
}//namespace irc
