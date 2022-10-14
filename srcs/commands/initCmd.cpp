#include "../../includes/includes.hpp"

using namespace irc;

mapCommand	Server::initCmd(void){
	mapCommand	ret;
	ret["NICK"] = &NICK;
	ret["USER"] = &USER;
	ret["PING"] = &ping;
	ret["PONG"] = &pong;
	return ret;
}
