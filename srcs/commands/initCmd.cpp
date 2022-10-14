#include "../../includes/includes.hpp"

using namespace irc;

mapCommand	Server::initCmd(void){
	mapCommand	ret;
	ret["NICK"] = &NICK;
	ret["USER"] = &USER;
	return ret;
}
