#include "../../includes/includes.hpp"

namespace irc
{
	void	JOIN(Server& serv, User& user, Command& cmd) {
		std::vector<std::string>                channel;
		std::vector<std::string>                key;
		std::vector<std::string>::iterator      itChan;
		std::vector<std::string>::iterator      itKey;
		if (cmd.params.size() < 1){
			std::cout << "ERR_NEEDMOREPARAMS\n"; 
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
		channel = split_target(cmd.params[0], ',', true);
		if (channel.size() > CHANNEL_MAX){
			user.sendCommand(ERR_TOOMANYCHANNELS());
			return;
		}
		if (cmd.params.size() == 1){
			for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
				if ((*itChan)[0] == '#' || (*itChan)[0] == '&'){
					if (serv.isInMapChannel(*itChan)){
						mapChannelIterator it = serv.getMapChannel().find(*itChan);
						if (it != serv.getMapChannel().end() && it->second.getPrivateBool()){
							user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
						}
						else if (it != serv.getMapChannel().end() && !it->second.isInBanList(user.getNickname())
							&& !it->second.isInChannel(user.getNickname())&& !it->second.getMods()._inviteOnly){
							it->second.joinChannel(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
						}
						else 
							user.sendCommand(ERR_BANNEDFROMCHAN(cmd.params[0]));
					}else {
						Channel chan = Channel(*itChan);
						serv.getMapChannel().insert(std::pair<std::string, Channel>(*itChan, chan));
						mapChannelIterator it = serv.getMapChannel().find(*itChan);
						it->second.joinChannel(user);
						it->second.addToOperatorList(user);
						it->second.sendMessage(S_JOIN(user, *itChan));
						std::cout << serv.getLog() << BLUE_BK << "Channels" << NC << BLUE << " Open: " << serv.getMapChannel().size() << NC << std::endl;
					}

				}
				else{
					user.sendCommand(ERR_NOSUCHCHANNEL(cmd.params[0]));	
				}
			}
		}
		else if (cmd.params.size() == 2){
			key = split_target(cmd.params[1], ',' , true);
			itKey = key.begin();
			for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
				if ((*itChan)[0] == '#' || (*itChan)[0] == '&'){
					if (serv.isInMapChannel(*itChan)){
						mapChannelIterator it = serv.getMapChannel().find(*itChan);
						if (it != serv.getMapChannel().end() && it->second.isInBanList(user.getNickname())){
							user.sendCommand(ERR_BANNEDFROMCHAN(cmd.params[0]));
						}
						else if (it != serv.getMapChannel().end() && it->second.getPrivateBool() && *itKey == it->second.getPassword()
							&& !it->second.isInChannel(user.getNickname()) && !it->second.getMods()._inviteOnly){
							it->second.joinChannel(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
							//message
							itKey++;
						}
					//	else if (it->second.getMods()._inviteOnly)
					//		ERR inviteon;u
						else if (it != serv.getMapChannel().end() && it->second.getPrivateBool() && itKey == key.end()){
							user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
						}
						else if (it != serv.getMapChannel().end() && !it->second.getPrivateBool()&& !it->second.getMods()._inviteOnly){
							if (itKey != key.end()){
								//message avec key
								itKey++;
							}
							it->second.joinChannel(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
						}
						else{
							user.sendCommand(ERR_BADCHANNELKEY(cmd.params[0]));
						} 
					}else {
						if (itKey != key.end() && key.size() > 0){
							Channel chan = Channel(*itChan, true, *itKey);
							serv.getMapChannel().insert(std::pair<std::string, Channel>(*itChan, chan));
							mapChannelIterator it = serv.getMapChannel().find(*itChan);
							it->second.joinChannel(user);
							it->second.addToOperatorList(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
							itKey++;
						}
						else {
							Channel chan = Channel(*itChan);
							serv.getMapChannel().insert(std::pair<std::string, Channel>(*itChan, chan));
							mapChannelIterator it = serv.getMapChannel().find(*itChan);
							it->second.joinChannel(user);
							it->second.addToOperatorList(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
						}
						std::cout << serv.getLog() << BLUE_BK << "Channels" << NC << BLUE << " Open: " << serv.getMapChannel().size() << NC << std::endl;
					}
				}
				else{
					user.sendCommand(ERR_NOSUCHCHANNEL(cmd.params[0]));	
				}
			}
		}
	}
}
