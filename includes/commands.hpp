#pragma once

#include "includes.hpp"

// void (*functionPtr)(Server&, User&, Command&)
namespace irc
{
	void NICK(Server& serv, User& user, Command& cmd);
	void USER(Server& serv, User& user, Command& cmd);
	/*
	void PING(Server& serv, User& user, Command& cmd);
	void JOIN(Server& serv, User& user, Command& cmd);
	void PRIVMSG(Server& serv, User& user, Command& cmd);
	*/
} // namespace irc
