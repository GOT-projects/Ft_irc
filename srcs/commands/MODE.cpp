#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command PASS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	MODE(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			std::cout << RED << serv.getLog() << "PASS: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("PASS", ""));
			return;
		}
		if (cmd.params[0][0] == '#' || cmd.params[0][0] == '&'){
			mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
			if(!it->second.isInOperatorList(user.getNickname())){
				std::cerr << "ERR_NOTINOPERLIST\n";
			}
			else {
				if (cmd.params[1][0] == 'k'){
					it->second.changeChanPassword(cmd.params[2]);
				}
				if (cmd.params[1][0] == 'p'){
					it->second.changePrivFlag();
				}
				if (cmd.params[1][0] == 'l'){
					int val = stoi(cmd.params[2]);
					if (val > 1)
						it->second.changeUserLimit(val);
					else
						std::cerr << "ERR_WRONGARGmdr\n";
				}
				if (cmd.params[1][0] == 'b'){
					User ban;
					ban.setNickname(cmd.params[2]);
					it->second.addToBanList(ban);
				}
				if (cmd.params[1][0] == 't'){
					it->second.getMods().changeTopicFlag();
				}
				if (cmd.params[1][0] == 'i'){
					it->second.getMods().changeInviteFlag();
				}
				if (cmd.params[1][0] == 's'){
					it->second.getMods().changeSecretFlag();
				}
				if (cmd.params[1] == "+o"){
					User op;
					op.setNickname(cmd.params[2]);
					it->second.giveRights(op);
				}
				if (cmd.params[1] == "-o"){
					User op;
					op.setNickname(cmd.params[2]);
					it->second.delFromOperatorList(op);
				}
			}
		}
	}
}
