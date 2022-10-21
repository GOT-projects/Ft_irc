#include "../../includes/includes.hpp"

namespace irc
{
	static void mode(Server& serv, User &user, Command& cmd, mapChannelIterator &id, char c, MODE_FLAG flag){
		c = ::tolower(c);
		switch (c) {
			case 'k':
				changePassword(cmd, id->second, flag);
				break;
			case 'l':
				try{
					changeUserLimitMode(cmd, id->second, flag);
				}catch (const std::exception& ){
					user.sendCommand(ERR_UMODEUNKNOWNFLAG(cmd.params[0]));
				}
				break;
			case 'p':
				changePrivateFlag(id->second, flag);
				break;
			case 'b':
				changeBanList(serv, cmd, id->second, flag);
				break;
			case 't':
				changeTopic(id->second, flag);
				break;
			case 'i':
				changeInvite(id->second, flag);
				break;
			case 's':
				changeSecret(id->second, flag);
				break;
			case 'o':
				changeOps(serv, cmd, id->second, flag);
				break;
			default:
				user.sendCommand(ERR_UMODEUNKNOWNFLAG(cmd.params[0]));
			
		}
	}
	/**
	 * @brief apply command PASS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	MODE(Server& serv, User& user, Command& cmd) {
		std::vector<std::string>                target;
		std::vector<std::string>::iterator      it;
		if (cmd.params.size() < 2) {
			//std::cout << RED << serv.getLog() << "MODE: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}else if (cmd.params[1].size() == 0 || cmd.params[1].size() > 2){
			//std::cout << RED << serv.getLog() << "MODE: ERROR flag " << NC << std::endl;
			user.sendCommand(ERR_UMODEUNKNOWNFLAG(cmd.params[0]));
			return;
		}
		mapChannelIterator id = serv.getMapChannel().find(cmd.params[0]);
		if ((cmd.params[0].size() > 0 && serv.isInMapChannel(cmd.params[0]) && id->second.isInOperatorList(user.getNickname())) &&
				(cmd.params[0][0] == '#' || cmd.params[0][0] == '&')){
			if (cmd.params[1].size() > 1 && cmd.params[1][0] == '+'){
				mode(serv, user, cmd, id, cmd.params[1][1],  MORE);
				return;
			}else if (cmd.params[1].size() > 1 && cmd.params[1][0] == '-'){
				mode(serv, user, cmd, id, cmd.params[1][1],  LESS);
				return;
			}else if (cmd.params[1].size() == 1){
				mode(serv, user, cmd, id, cmd.params[1][0],  NORM);
				return;
			}
		} else if (user.isOperatorServer()) {
			User	tmpUser;
			tmpUser.setNickname(cmd.params[0]);
			if (cmd.params[0][0] == '@')
				tmpUser.setNickname(cmd.params[0].substr(1));
			User	*target = getUserInList(tmpUser, serv.getOnlineUsers(), &isSameNickname);
			if (!target) {
				user.sendCommand(ERR_NOSUCHNICK(user, tmpUser.getNickname()));
				return;
			} else if (user.getNickname() == tmpUser.getNickname()
				&& cmd.params[1].size() > 1 && cmd.params[1][0] == '-' && cmd.params[1][1] == 'o'){
					user.beOperatorServer(false);
					return;
			}
		}
		user.sendCommand(ERR_UMODEUNKNOWNFLAG(cmd.params[0]));
	}
}
