#pragma once

/**
 * @brief Header file that contain define that server use to reply at clients
 */

// Delimiter of a request
#define END "\r\n"

#define	PING(origin)				("PING " + origin + END)
#define	PONG(origin)				(":" + origin + " PONG " + origin + END)
#define	PRIVMSG(target, message)	("PRIVMSG " + target + " :" + message)



//Error general
#define ERR_NOORIGIN(user)			(user + ":No origin specified\r\n") //409
#define ERR_NEEDMOREPARAMS(command)	(command + " :Not enough parameters" + END)//461 

//Error Nick
#define ERR_ERRONEUSNICKNAME(nick)	(nick + ":Erroneus nickname" + END) //432 
#define ERR_NICKNAMEINUSE(nick)		(nick + " :Nickname is already in use" + END) //433 
 
//Error User
#define ERR_ALREADYREGISTERED()		(":You may not reregister\r\n") //462 
