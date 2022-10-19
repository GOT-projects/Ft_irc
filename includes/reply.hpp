#pragma once

#include "includes.hpp"

/**
 * @brief Header file that contain define that server use to reply at clients
 */

// Delimiter of a request
#define END "\r\n"
#define CHANNEL_MAX 100

#define RPL_WELCOME(nickname)		("001 " + nickname + " :Welcome to the ft_irc_serv_42_Lyon, " + std::string(nickname))
#define	PING(origin)				("PING " + origin)
#define	PONG(origin)				(":" + origin + " PONG " + origin)
#define	S_PRIVMSG(client, target, message)	(":" + client.getNickname() + "!" + client.getUsername() + "@" + user.getServername() + " PRIVMSG " + target + " :" + message)
#define	S_JOIN(client, target)	(":" + client.getNickname() + "!" + client.getUsername() + "@" + user.getServername() + " JOIN " + target)

// PASS
#define ERR_PASSWDMISMATCH()		("464 :Password incorrect") // 464

//Error general
#define ERR_NOORIGIN()				(":No origin specified") //409
#define ERR_NEEDMOREPARAMS(command, param)	(std::string(command) + " :Not enough parameters " + std::string(param)) //461 

//Error Nick
#define ERR_NONICKNAMEGIVEN()		(":No nickname given") // 321
#define ERR_ERRONEUSNICKNAME(nick)	(nick + " :Erroneus nickname") // 432 nickname not valid
#define ERR_NICKNAMEINUSE(nick)		(nick + " :Nickname is already in use") //433 
 
//Error User
#define ERR_ALREADYREGISTERED()		(":You may not reregister") // 462

#define ERR_TOOMANYCHANNELS()       ("405 :You have joined too many channels") //405
                                                                               
#define ERR_NOSUCHNICK(nickname)        (std::string(nickname) + " 401 :No such nick/channel")       //405

#define ERR_UNKNOWNCOMMAND(command)    (std::string(command) + " 421 :Unknown command")          //421

//INFO
#define RPL_INFO(text)                  ("371 INFO: " + std::string(text))
#define RPL_ENDOFINFO()                 ("374 INFO: End of INFO list")  

//HELP
#define ERR_HELPNOTFOUND(suject)        ("524 " + std::string(suject) + " :No help available on this topic")
#define RPL_HELPSTART(text)             ("704 :" + std::string(text))
#define RPL_HELPTXT(text)               ("705 :" + std::string(text))
#define RPL_ENDOFHELP(text)             ("706 :" + std::string(text))

//VERSION
#define ERR_NOSUCHSERVER(servername)    ("402 " + std::string(servername) + " :No such server")
#define RPL_VERSION(version, server, comment)    ("351 " + std::string(version) + " " + std::string(server) + " :" + std::string(comment))

//TIME
#define RPL_TIME(server, time)   ("391 " + std::string(server) + " :" + std::string(time))
