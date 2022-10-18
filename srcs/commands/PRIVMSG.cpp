
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
		//TODO check register
		//TODO check add BANNED LIST user
		//TODO ERR_NOSUCHNICK (401)
		//TODO ERR_NOSUCHSERVER (402)
		//TODO ERR_CANNOTSENDTOCHAN (404)
		//TODO ERR_TOOMANYTARGETS (407)
		//TODO ERR_NORECIPIENT (411)
		//TODO ERR_NOTEXTTOSEND (412)
		//TODO ERR_NOTOPLEVEL (413)
		//TODO ERR_WILDTOPLEVEL (414)
		//TODO RPL_AWAY (301)

		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "PRIVMSG: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}
		if (cmd.params[0][0] == '#'){
			mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
            it->second.sendMessage(S_PRIVMSG(user, cmd.params[0], cmd.params[1]), user);
		}
		else {
			User tmp;
			tmp.setNickname(cmd.params[0]);
			User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
			userSend->sendCommand(S_PRIVMSG(user, cmd.params[0], cmd.params[1]));
		}
	}
} // namespace irc
