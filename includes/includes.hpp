#pragma once

// c++
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <list>
#include <vector>
#include <cctype>
#include <sstream>
#include <fstream>


// Réseau
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <iomanip>

// Utils
#include <stdlib.h>
#include <stdio.h>
#include <ctime>

// Error
#include <signal.h>
#include <errno.h>
#include <string.h>

// Our code

#include "define.hpp"
#include "log/log.hpp"
#include "utils/string.hpp"
#include "Parsing.hpp"
#include "user/UserMode.hpp"
#include "user/User.hpp"
#include "channel/ChannelMode.hpp"
#include "bot/bot.hpp"
#include "channel/Channel.hpp"
#include "Server.hpp"
#include "utils/compare.hpp"
#include "commands.hpp"
#include "reply.hpp"


namespace irc{
	enum MODE_FLAG{
		MORE, LESS, NORM
	};
	void changePassword(irc::Command &cmd, irc::Channel &channel,  MODE_FLAG flag);
	void changePrivateFlag(irc::Channel &channel,  MODE_FLAG flag);
	void changeBanList(irc::Server &serv, irc::Command &cmd, irc::Channel &channel,  MODE_FLAG flag);
	void changeTopic(irc::Channel &channel,  MODE_FLAG flag);
	void changeInvite(irc::Channel &channel,  MODE_FLAG flag);
	void changeSecret(irc::Channel &channel,  MODE_FLAG flag);
	void changeOps(irc::Server &serv, irc::Command &cmd, irc::Channel &channel,  MODE_FLAG flag);
	void changeUserLimitMode(irc::Command &cmd, irc::Channel &channel,  MODE_FLAG flag);
}
