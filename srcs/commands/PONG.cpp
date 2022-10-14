
#include "../../includes/includes.hpp"

namespace irc
{
	void pong(Server&, User& user, Command& cmd) {
        user.sendCommand(PING(cmd.params[0]));
    };

}//namespace irc
