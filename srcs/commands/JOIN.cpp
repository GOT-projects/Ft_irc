
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
		//              JOIN #foo,#bar                  ; join channels #foo and #bar.  @handle

        //    ERR_INVITEONLYCHAN             
        //    ERR_CHANNELISFULL               ERR_BADCHANMASK
        //    ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
        //    ERR_TOOMANYTARGETS              ERR_UNAVAILRESOURCE
        //    RPL_TOPIC
		//              
		channel = split_target(cmd.params[0]);
		if (channel.size() > CHANNEL_MAX){
			user.sendCommand(ERR_TOOMANYCHANNELS());
			return;
		}
		if (cmd.params.size() == 1){
			std::cout << "Channel: \n";
			for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
				std::cout << "\n\t\t chan " << *itChan << std::endl;
				if (serv.isInMapChannel(*itChan)){
					mapChannelIterator it = serv.getMapChannel().find(*itChan);
					if (!it->second.isInBanList(user.getNickname())){
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
					it->second.sendMessage(S_JOIN(user, *itChan));
				}
			}
		}else if (cmd.params.size() == 2){
			key = split_target(cmd.params[1]);
			std::cout << "Channel: \n";
			itKey = key.begin();
			for (itChan = channel.begin(); itChan != channel.end(); ++itChan){
				std::cout << "\n\t\t chan " << *itChan << std::endl;
				if (serv.isInMapChannel(*itChan)){
					mapChannelIterator it = serv.getMapChannel().find(*itChan);
					if (it->second.getPrivateBool() && *itKey == it->second.getPassword()){
						it->second.joinChannel(user);
						it->second.sendMessage(S_JOIN(user, *itChan));
						//message
						itKey++;
					}
					else if (it->second.getPrivateBool() && itKey == key.end())
						std::cout << "ERR_NEEDMOREPARAMS\n";
					else 
						std::cout << "ERR_BADCHANNELKEY\n";
					// else {
					// 	// comment on gere les mdp . aucune precision sur internet -> si chan ouvert on marque quand mm la key meme si elle sert a rien. en gros on va faire un chan une key
					// 	it->second.joinChannel(user);
					// 	it->second.sendMessage(S_JOIN(user, *itChan));
					// }
				}else {
					// est ce que si une key est precisé on ouvre direct le chan en mode private + mdp?
					Channel chan = Channel(*itChan);
					serv.getMapChannel().insert(std::pair<std::string, Channel>(*itChan, chan));
					mapChannelIterator it = serv.getMapChannel().find(*itChan);
					it->second.joinChannel(user);
					it->second.sendMessage(S_JOIN(user, *itChan));
				}
			}
		}
	}

	// void	QUIT(Server& serv, User& user, Command& cmd) {
	//     if (cmd.params.size() < 1){
	//         std::cout << "ERR_NEEDMOREPARAMS\n"; 
	//         return;
	//     }
	//     // check des channel dans le tableau de channel
	//     if (serv.isInMapChannel(cmd.params[0]))
	//     {
	//         mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
	//         it->second.joinChannel(user);
	//         it->second.sendMessage(S_JOIN(user, cmd.params[0]));
	//     }
	//     else {
	//         Channel chan = Channel(cmd.params[0]);
	//         serv.getMapChannel().insert(std::pair<std::string, Channel>(cmd.params[0], chan));
	//         mapChannelIterator it = serv.getMapChannel().find(cmd.params[0]);
	//         it->second.joinChannel(user);
	//         it->second.sendMessage(S_JOIN(user, cmd.params[0]));
			
	//         //message a renvoyé
	//     }
	// }
}