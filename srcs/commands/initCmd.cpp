#include "../../includes/includes.hpp"

using namespace irc;

/**
 * @brief static member function of Server class which construct
 * the map of commands
 * 
 * @return mapCommand a map <commandName - functionCommand>
 */
mapCommand	Server::initCmd(void){
	mapCommand	ret;
	ret["PRIVMSG"] = &PRIVMSG;
	ret["NICK"] = &NICK;
	ret["PASS"] = &PASS;
	ret["PING"] = &ping;
	ret["PONG"] = &pong;
	ret["USER"] = &USER;
	ret["CAP"] = &CAP;
	return ret;
}
