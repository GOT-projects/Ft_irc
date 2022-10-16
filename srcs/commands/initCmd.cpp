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
	ret["PASS"] = &PASS;
	ret["NICK"] = &NICK;
	ret["USER"] = &USER;
	ret["PING"] = &ping;
	ret["PONG"] = &pong;
	return ret;
}
