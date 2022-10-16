#pragma once

#include "includes.hpp"

/**
 * @brief Header file that contain define that server use to reply at clients
 */

// Delimiter of a request
#define END "\r\n"

#define	PING(origin)				("PING " + origin + END)
#define	PONG(origin)				(":" + origin + " PONG " + origin + END)
#define	PRIVMSG(target, message)	("PRIVMSG " + target + " :" + message)

// PASS
#define ERR_PASSWDMISMATCH()		(":Password incorrect\r\n") // 464

//Error general
#define ERR_NOORIGIN()			(":No origin specified\r\n") //409
#define ERR_NEEDMOREPARAMS(command)	(std::string(command) + " :Not enough parameters" + END)//461 

//Error Nick
#define ERR_NONICKNAMEGIVEN()		(":No nickname given\r\n") // 321
#define ERR_ERRONEUSNICKNAME(nick)	(nick + " :Erroneus nickname" + END) // 432 nickname not valid
#define ERR_NICKNAMEINUSE(nick)		(nick + " :Nickname is already in use" + END) //433 
 
//Error User
#define ERR_ALREADYREGISTERED()		(":You may not reregister\r\n") // 462