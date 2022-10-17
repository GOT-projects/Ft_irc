#pragma once

#include "includes.hpp"

/**
 * @brief Header file that contain define that server use to reply at clients
 */

// Delimiter of a request
#define END "\r\n"

#define RPL_WELCOME(nickname)		("001 " + nickname + " :Welcome to the ft_irc_serv_42_Lyon, " + std::string(nickname))
#define	PING(origin)				("PING " + origin)
#define	PONG(origin)				(":" + origin + " PONG " + origin)
#define	S_PRIVMSG(client, target, message)	(":" + client.getNickname() + "!" + client.getUsername() + "@" + user.getServername() + " PRIVMSG " + target + " :" + message)
#define	S_JOIN(client, target)	(":" + client.getNickname() + "!" + client.getUsername() + "@" + user.getServername() + " JOIN " + target)

// PASS
#define ERR_PASSWDMISMATCH()		("464 :Password incorrect") // 464

//Error general
#define ERR_NOORIGIN()				(":No origin specified") //409
#define ERR_NEEDMOREPARAMS(command)	(std::string(command) + " :Not enough parameters") //461 

//Error Nick
#define ERR_NONICKNAMEGIVEN()		(":No nickname given") // 321
#define ERR_ERRONEUSNICKNAME(nick)	(nick + " :Erroneus nickname") // 432 nickname not valid
#define ERR_NICKNAMEINUSE(nick)		(nick + " :Nickname is already in use") //433 
 
//Error User
#define ERR_ALREADYREGISTERED()		(":You may not reregister") // 462
