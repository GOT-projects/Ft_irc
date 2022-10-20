
#include "../../includes/includes.hpp"

namespace irc{
	void changeUserLimitMode(Command &cmd, Channel& channel,  MODE_FLAG flag){
		int limit(std::stoi(cmd.params[2]));
	
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
	
	void changePassword(Command &cmd, Channel channel,  MODE_FLAG flag){
	
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
	
	void changePrivateFlag(Channel channel,  MODE_FLAG flag){
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
	
	void changeBanList(Command &cmd, Channel channel,  MODE_FLAG flag){
		if (flag == MORE){
			if (!channel.isInBanList(cmd.params[2])){
				User ban;
				ban.setNickname(cmd.params[2]);
				channel.addToBanList(ban);
			}
		}else if (flag == LESS){
			if (channel.isInBanList(cmd.params[2])){
				User ban;
				ban.setNickname(cmd.params[2]);
				channel.delFromBansList(ban);
			}
		}else if (flag == NORM){
			if (!channel.isInBanList(cmd.params[2])){
				User ban;
				ban.setNickname(cmd.params[2]);
				channel.addToBanList(ban);
			}else{
				User ban;
				ban.setNickname(cmd.params[2]);
				channel.delFromBansList(ban);
			}
		}
	}
	
	void changeTopic(Channel channel,  MODE_FLAG flag){
		if (flag == MORE){
			channel.getMods().changeTopicFlag(true);
		}else if (flag == LESS){
			channel.getMods().changeTopicFlag(false);
		}else if (flag == NORM){
			channel.getMods().changeTopicFlag();
		}
	}
	
	void changeInvite(Channel channel,  MODE_FLAG flag){
		if (flag == MORE){
			channel.getMods().changeInviteFlag(true);
		}else if (flag == LESS){
			channel.getMods().changeInviteFlag(false);
		}else if (flag == NORM){
			channel.getMods().changeInviteFlag();
		}
	}
	
	void changeSecret(Channel channel,  MODE_FLAG flag){
		if (flag == MORE){
			channel.getMods().changeSecretFlag(true);
		}else if (flag == LESS){
			channel.getMods().changeSecretFlag(false);
		}else if (flag == NORM){
			channel.getMods().changeSecretFlag();
		}
	}
	
	void changeOps(Command &cmd, Channel channel,  MODE_FLAG flag){
		if (flag == MORE){
			if (!channel.isInOperatorList(cmd.params[2])){
				User op;
				op.setNickname(cmd.params[2]);
				channel.addToOperatorList(op);
			}
		}else if (flag == LESS){
			if (channel.isInOperatorList(cmd.params[2])){
				User op;
				op.setNickname(cmd.params[2]);
				channel.delFromOperatorList(op);
			}
		}else if (flag == NORM){
			if (!channel.isInOperatorList(cmd.params[2])){
				User op;
				op.setNickname(cmd.params[2]);
				channel.addToOperatorList(op);
			}else{
				User op;
				op.setNickname(cmd.params[2]);
				channel.delFromOperatorList(op);
			}
		}
	}
};
