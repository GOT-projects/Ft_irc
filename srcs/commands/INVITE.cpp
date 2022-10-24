#include "../../includes/includes.hpp"

namespace irc
{
	void	INVITE(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 2) {
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
		mapChannelIterator it = serv.getMapChannel().find(cmd.params[1]);
		if (it == serv.getMapChannel().end()) {
			user.sendCommand(ERR_NOSUCHCHANNEL(cmd.params[1]));
			return;
		}
		if (!(it->second.isInChannel(user.getNickname()))) {
			user.sendCommand(ERR_NOTONCHANNEL(user.getNickname(), cmd.params[1]));
			return;
		}
		if (it->second.getMods()._inviteOnly && !(it->second.isInOperatorList(user.getNickname()))) {
			user.sendCommand(ERR_CHANOPRIVSNEEDED(cmd.params[1]));
			return;
		}
		if (it->second.isInChannel(cmd.params[0])) {
			user.sendCommand(ERR_USERONCHANNEL(cmd.params[0], cmd.params[1]));
			return;
		}
		User	tmp;
		tmp.setNickname(cmd.params[0]);
		User*	newUser = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
		if (newUser) {
			it->second.joinChannel(*newUser);
			newUser->sendCommand(S_INVITE(user.getNickname(), cmd.params[0], cmd.params[1]));
			it->second.sendMessage(RPL_INVITING(user.getNickname(), cmd.params[0], cmd.params[1]));
			it->second.sendMessage(S_JOIN((*newUser), cmd.params[1]));
		}
	}
} // namespace irc

