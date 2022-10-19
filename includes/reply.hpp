#pragma once

#include "includes.hpp"

/**
 * @brief Header file that contain define that server use to reply at clients
 */

// Delimiter of a request
#define END "\r\n"
#define CHANNEL_MAX 100

#define RPL_PREFIX(client)	(":" + client.getNickname() + "!" + client.getUsername() + "@" + user.getServername() + " ")
#define RPL_HOST(client)	(":" + user.getServername() + " ")

#define RPL_WELCOME(nickname)				("001 " + nickname + " :Welcome to the ft_irc_serv_42_Lyon, " + std::string(nickname))
#define	PING(origin)						("PING " + origin)
#define	PONG(origin)						(":" + origin + " PONG " + origin)
#define	S_PRIVMSG(client, target, message)	(RPL_PREFIX(client) + "PRIVMSG " + target + " :" + message)
#define	S_NOTICE(client, target, message)	(RPL_PREFIX(client) + "NOTICE " + target + " :" + message)
#define	S_JOIN(client, target)				(RPL_PREFIX(client) + "JOIN " + target)

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

#define ERR_TOOMANYCHANNELS()       ("405 :You have joined too many channels") //405
                                                                               
#define ERR_NOSUCHNICK(client, nickname)        (RPL_HOST(client) + "401 " + nickname + " :No such nick/channel")       //405

#define ERR_UNKNOWNCOMMAND(command)    (std::string(command) + " 421 :Unknown command")          //421

#define RPL_INFO(text)                  ("371 INFO: " + std::string(text))
#define RPL_ENDOFINFO()                 ("374 INFO: End of INFO list")  

// channel
#define ERR_CANNOTSENDTOCHAN(client, target)	(RPL_PREFIX(client) + target + " : Cannot send to channel")
