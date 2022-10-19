#pragma once

#include "includes.hpp"

// void (*functionPtr)(Server&, User&, Command&)
namespace irc
{
	/**
	 * @brief All functions in this file are the different command that
	 * the server have to answer
	 */

	bool	canRegister(const User& user, const std::string& cmd, Server& serv);
	bool	canExecute(const User& user, const std::string& cmd, Server& serv);

	void	JOIN(Server& serv, User& user, Command& cmd);
	void	TOPIC(Server& serv, User& user, Command& cmd);
	void	MODE(Server& serv, User& user, Command& cmd);
	void	NAMES(Server& serv, User& user, Command& cmd);
	void	PASS(Server& serv, User& user, Command& cmd);
	void	NICK(Server& serv, User& user, Command& cmd);
	void	USER(Server& serv, User& user, Command& cmd);
	void	ping(Server& , User& user, Command& cmd);
	void	pong(Server& serv, User& user, Command& cmd);
	void	CAP(Server& serv, User& user, Command& cmd);
	void	PRIVMSG(Server& serv, User& user, Command& cmd);
	void	INFO(Server& serv, User& user, Command& cmd);
	void	QUIT(Server& serv, User& user, Command& cmd);
	/*
	void JOIN(Server& serv, User& user, Command& cmd);
	void PRIVMSG(Server& serv, User& user, Command& cmd);
	*/
} // namespace irc
