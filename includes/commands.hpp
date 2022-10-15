#pragma once

#include "includes.hpp"

// void (*functionPtr)(Server&, User&, Command&)
namespace irc
{
	/**
	 * @brief All functions in this file are the different command that
	 * the server have to answer
	 */


	void NICK(Server& serv, User& user, Command& cmd);
	void USER(Server& serv, User& user, Command& cmd);
	void ping(Server& , User& user, Command& cmd);
	void pong(Server& serv, User& user, Command& cmd);
	/*
	void JOIN(Server& serv, User& user, Command& cmd);
	void PRIVMSG(Server& serv, User& user, Command& cmd);
	*/
} // namespace irc
