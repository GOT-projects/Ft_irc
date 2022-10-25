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
	bool	canExecute(Server& serv, const User& user, const std::string& cmd);

	void	JOIN(Server& serv, User& user, Command& cmd);
	void	KICK(Server& serv, User& user, Command& cmd);
	void	PART(Server& serv, User& user, Command& cmd);
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
	void	NOTICE(Server& serv, User& user, Command& cmd);
	void	INFO(Server& serv, User& user, Command& cmd);
	void	KILL(Server& serv, User& user, Command& cmd);
	void	HELP(Server& serv, User& user, Command& cmd);
	void	VERSION(Server& serv, User& user, Command& cmd);
	void	LUSERS(Server& serv, User& user, Command& cmd);
	void	TIME(Server& serv, User& user, Command& cmd);
	void	QUIT(Server& serv, User& user, Command& cmd);
	void	OPER(Server& serv, User& user, Command& cmd);
	void	INVITE(Server& serv, User& user, Command& cmd);
} // namespace irc
