#include "../../includes/includes.hpp"

namespace irc
{
	void	JOIN(Server& serv, User& user, Command& cmd) {
		std::vector<std::string>                channel;
		std::vector<std::string>                key;
		std::vector<std::string>::iterator      itChan;
		std::vector<std::string>::iterator      itKey;
		if (!canExecute(user, cmd.command, serv))
			return;
		if (cmd.params.size() < 1){
			std::cout << "ERR_NEEDMOREPARAMS\n"; 
			user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
			return;
		}
		//split params[0] if have ',' for open multi channel
		//TODO need use target for go or home new channel 
		//and need check target[0] = '#' || '&' || '@' for change the oper of the channel
		//TODO for test use cmd:   \join #test,#tes1,#tes2,&test3
		//Example list
		//              JOIN #foobar                    ; join channel #foobar.  @Handle
		//              JOIN &foo fubar                 ; join channel &foo using key "fubar".
		//              JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
		//                                              and &bar using no key.
		//              
		//              JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
		//                                              and channel #bar using key "foobar".
		//              
		//              JOIN #foo,#bar                  ; join channels #foo and #bar.

        //    ERR_INVITEONLYCHAN             
        //    ERR_CHANNELISFULL               ERR_BADCHANMASK
        //      ERR_TOOMANYCHANNELS
        //    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
        //    RPL_TOPIC

		channel = split_target(cmd.params[0]);
		if (channel.size() > CHANNEL_MAX){
			user.sendCommand(ERR_TOOMANYCHANNELS());
			return;
		}
		if (cmd.params.size() == 1){
			std::cout << "Channel: \n";
			for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
				std::cout << "\n\t\t chan " << *itChan << std::endl;
				if ((*itChan)[0] == '#' || (*itChan)[0] == '&'){
					if (serv.isInMapChannel(*itChan)){
						std::cerr << "CXGrtxwetcgerg\n";
						mapChannelIterator it = serv.getMapChannel().find(*itChan);
						if (it->second.getPrivateBool()){
							std::cerr << "ERR_NEEDMOREPARAMS\n";
							user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
						}
						else if (!it->second.isInBanList(user.getNickname())){
							it->second.joinChannel(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
						}
						else 
							std::cout << "ERR_BANNEDFROMCHAN\n";
					}else {
						Channel chan = Channel(*itChan);
						serv.getMapChannel().insert(std::pair<std::string, Channel>(*itChan, chan));
						mapChannelIterator it = serv.getMapChannel().find(*itChan);
						it->second.joinChannel(user);
						it->second.addToOperatorList(user);
						it->second.sendMessage(S_JOIN(user, *itChan));
					}

				}
				else{
					std::cout << "ERR_NOSUCHCHANNEL\n"; //pas de # ou &
					user.sendCommand(ERR_NOSUCHCHANNEL(cmd.params[0]));	
				}
			}
		}
		else if (cmd.params.size() == 2){
			key = split_target(cmd.params[1]);
			std::cout << "Channel: \n";
			itKey = key.begin();
			for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
				std::cout << "\n\t\t chan " << *itChan << std::endl;
				if ((*itChan)[0] == '#' || (*itChan)[0] == '&'){
					if (serv.isInMapChannel(*itChan)){
						std::cerr << "CXGrtxwetcgerg\n";
						mapChannelIterator it = serv.getMapChannel().find(*itChan);
						if (it->second.isInBanList(user.getNickname())){
							std::cout << "ERR_BANNEDFROMCHAN\n";
							user.sendCommand(ERR_BANNEDFROMCHAN(cmd.params[0]));
						}
						else if (it->second.getPrivateBool() && *itKey == it->second.getPassword()){
							it->second.joinChannel(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
							//message
							itKey++;
						}
						else if (it->second.getPrivateBool() && itKey == key.end()){
							std::cout << "ERR_NEEDMOREPARAMS\n";
							user.sendCommand(ERR_NEEDMOREPARAMS(cmd.command, ""));
						}
						else if (!it->second.getPrivateBool()){
							if (itKey != key.end()){
								//message avec key
								itKey++;
							}
							it->second.joinChannel(user);
							it->second.sendMessage(S_JOIN(user, *itChan));
						}
						else{
							std::cout << "ERR_BADCHANNELKEY\n";
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
					}
				}
				else{
					std::cout << "ERR_NOSUCHCHANNEL\n"; //pas de # ou &
					user.sendCommand(ERR_NOSUCHCHANNEL(cmd.params[0]));	
				}
			}
		}
	}
}
