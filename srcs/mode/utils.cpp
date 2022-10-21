
#include "../../includes/includes.hpp"

namespace irc{
	void changeUserLimitMode(Command &cmd, Channel& channel,  MODE_FLAG flag){
		int limit(atoi(cmd.params[2].c_str()));
	
		if (limit < 0){
			throw;
		}
		if (flag == MORE){
			channel.changeUserLimit(limit);
		}else if (flag == LESS){
			channel.changeUserLimit(0);
		}else if (flag == NORM){
			channel.changeUserLimit(limit);
		}else{
			std::cerr << "Problem" << std::endl;
		}
	}
	
	void changePassword(Command &cmd, Channel &channel,  MODE_FLAG flag){
	
		if (flag == MORE){
			if (!channel.getPrivateBool())
				channel.changePrivFlag(true);
			channel.changeChanPassword(cmd.params[2]);
		}else if (flag == LESS){
			if (channel.getPrivateBool())
				channel.changePrivFlag(false);
			channel.changeChanPassword("");
		}else if (flag == NORM){
			if (cmd.params.size() == 3){
				if (!channel.getPrivateBool())
					channel.changePrivFlag(true);
				channel.changeChanPassword(cmd.params[2]);
			}else if (cmd.params.size() == 2){
				if (channel.getPrivateBool())
					channel.changePrivFlag(false);
				channel.changeChanPassword("");
			}
		}else{
			std::cerr << "Problem" << std::endl;
		}
	}
	
	void changePrivateFlag(Channel &channel,  MODE_FLAG flag){
		if (flag == MORE){
			if (!channel.getPrivateBool())
				channel.changePrivFlag(true);
		}else if (flag == LESS){
			if (channel.getPrivateBool())
				channel.changePrivFlag(false);
		}else if (flag == NORM){
			channel.changePrivFlag();
		}
	}
	
	void changeBanList(Server& serv, Command &cmd, Channel &channel,  MODE_FLAG flag){
		if (flag == MORE){
			if (!channel.isInBanList(cmd.params[2])){
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.addToBanList(*userSend);
			}
		}else if (flag == LESS){
			if (channel.isInBanList(cmd.params[2])){
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.delFromBansList(*userSend);
			}
		}else if (flag == NORM){
			if (!channel.isInBanList(cmd.params[2])){
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.addToBanList(*userSend);
			}else{
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.delFromBansList(*userSend);
			}
		}
	}
	
	void changeTopic(Channel &channel,  MODE_FLAG flag){
		if (flag == MORE){
			channel.getMods().changeTopicFlag(true);
		}else if (flag == LESS){
			channel.getMods().changeTopicFlag(false);
		}else if (flag == NORM){
			channel.getMods().changeTopicFlag();
		}
	}
	
	void changeInvite(Channel &channel,  MODE_FLAG flag){
		if (flag == MORE){
			channel.getMods().changeInviteFlag(true);
		}else if (flag == LESS){
			channel.getMods().changeInviteFlag(false);
		}else if (flag == NORM){
			channel.getMods().changeInviteFlag();
		}
	}
	
	void changeSecret(Channel &channel,  MODE_FLAG flag){
		if (flag == MORE){
			channel.getMods().changeSecretFlag(true);
		}else if (flag == LESS){
			channel.getMods().changeSecretFlag(false);
		}else if (flag == NORM){
			channel.getMods().changeSecretFlag();
		}
	}
	
	void changeOps(Server &serv, Command &cmd, Channel &channel,  MODE_FLAG flag){
		if (flag == MORE){
			if (!channel.isInOperatorList(cmd.params[2])){
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.addToOperatorList(*userSend);
			}
		}else if (flag == LESS){
			if (channel.isInOperatorList(cmd.params[2])){
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.delFromOperatorList(*userSend);
			}
		}else if (flag == NORM){
			if (!channel.isInOperatorList(cmd.params[2])){
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.addToOperatorList(*userSend);
			}else{
				User tmp;
				tmp.setNickname(cmd.params[2]);
				User *userSend = getUserInList(tmp, serv.getOnlineUsers(), &isSameNickname);
				channel.delFromOperatorList(*userSend);
			}
		}
	}
};
