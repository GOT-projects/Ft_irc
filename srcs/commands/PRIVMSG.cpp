
#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command COPA
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	PRIVMSG(Server& serv, User& user, Command& cmd) {
		std::vector<std::string>			target;
		std::vector<std::string>::iterator	it;
		if (cmd.params.size() < 2){
			std::cerr << RED << serv.getLog() << "PRIVMSG: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
		target = split_target(cmd.params[0], ',', true);
		cmd.params[1] = serv.getBot().blacklistMsg(cmd.params[1]);
		for (it = target.begin(); it != target.end(); ++it){
			//std::cout << "target " << *it <<std::endl;
			// user
			if (it->find("#") == std::string::npos && it->find("&") == std::string::npos) {
				User tmp;
				tmp.setNickname(*it);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				if (userSend != NULL) {
					userSend->sendCommand(S_PRIVMSG(user, *it, cmd.params[1]));
				}
				else {
					user.sendCommand(ERR_NOSUCHNICK(user, *it));
				}
			} else { // channel
				std::string::size_type	pos = it->find("@");
				mapChannelIterator		chan;
				mapChannelIterator		end = serv.getMapChannel().end();
				if (pos == 0 && (it->find("#") == 1 || it->find("&") == 1) && (chan = serv.getMapChannel().find(it->substr(1))) != end
					&& chan->second.isInChannel(user.getNickname())) // opchan
					chan->second.sendMessageToOper(S_PRIVMSG(user, *it, cmd.params[1]), user);
				else if (pos == std::string::npos && (it->find("#") == 0 || it->find("&") == 0) && (chan = serv.getMapChannel().find(*it)) != end
					&& chan->second.isInChannel(user.getNickname())) // all users
					chan->second.sendMessage(S_PRIVMSG(user, *it, cmd.params[1]), user);
				else
					user.sendCommand(ERR_CANNOTSENDTOCHAN(user, *it));
			}
		}
	}
} // namespace irc
