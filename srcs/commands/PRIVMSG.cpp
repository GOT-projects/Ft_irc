
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
		if (!canExecute(user, cmd.command, serv))
			return;
        std::vector<std::string>                target;
        std::vector<std::string>::iterator      it;
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

		if (cmd.params.size() < 1){
			std::cerr << RED << serv.getLog() << "PING: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS());
			return;
		}
        target = split_target(cmd.params[0]);
        for (it = target.begin(); it != target.end(); ++it){
            //TODO need work here end send msg to the target 
            std::cout << "target " << *it <<std::endl;
			User tmp;
			tmp.setNickname(*it);
			User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
            if (userSend != NULL){
			    userSend->sendCommand(S_PRIVMSG(user, *it, cmd.params[1]));
            }else{
			    user.sendCommand(ERR_NOSUCHNICK(*it));

            }
        }

		/* if (cmd.params[0][0] == '#'){ */
		/* 	mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]); */
            /* it->second.sendMessage(S_PRIVMSG(user, cmd.params[0], cmd.params[1])); */
		/* } */
		/* else { */
			/* User tmp; */
			/* tmp.setNickname(cmd.params[0]); */
			/* User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname); */
			/* userSend->sendCommand(S_PRIVMSG(user, cmd.params[0], cmd.params[1])); */
		/* } */
	}
} // namespace irc
