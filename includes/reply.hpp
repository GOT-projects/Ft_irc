#pragma once

#include "includes.hpp"

/**
 * @brief Header file that contain define that server use to reply at clients
 */

// Delimiter of a request
#define END "\r\n"
#define CHANNEL_MAX 100

#define RPL_PREFIX(client)	(":" + client.getNickname() + "!" + client.getUsername() + "@" + user.getServername() + " ")
#define RPL_HOST(client)	(":" + client.getServername() + " ")

#define RPL_WELCOME(nickname)				("001 " + nickname + " :Welcome to the ft_irc_serv_42_Lyon, " + std::string(nickname))
#define	PING(origin)						("PING " + origin)
#define	PONG(origin)						(":" + origin + " PONG " + origin)
#define	S_PRIVMSG(client, target, message)	(RPL_PREFIX(client) + "PRIVMSG " + target + " :" + message)
#define	S_NOTICE(client, target, message)	(RPL_PREFIX(client) + "NOTICE " + target + " :" + message)
#define	S_JOIN(client, target)				(RPL_PREFIX(client) + "JOIN " + target)
#define	S_KICK(user, channel, target)		(":" + user + " KICK " + channel + " " + target)
#define	S_PART(user, channel)			    (RPL_PREFIX(user) + " PART " + channel)

#define RPL_YOUREOPER()						("381 :You are now an IRC operator")
#define ERR_NOOPERHOST(nick)					("491 " + nick + " :No O-lines for your host")

// PASS
#define ERR_PASSWDMISMATCH()		("464 :Password incorrect") // 464

//Error general
#define ERR_NOORIGIN()				("409 :No origin specified") //409
#define ERR_NEEDMOREPARAMS(command, param)	("463 " + std::string(command) + " :Not enough parameters " + std::string(param)) //461 

//Error Nick
#define ERR_NONICKNAMEGIVEN()		("321 :No nickname given") // 321
#define ERR_ERRONEUSNICKNAME(nick)	("432 " + nick + " :Erroneus nickname") // 432 nickname not valid
#define ERR_NICKNAMEINUSE(nick)		("433 " + nick + " :Nickname is already in use") //433 
 
//Error User
#define ERR_ALREADYREGISTERED()		("432 :You may not reregister") // 462

#define ERR_TOOMANYCHANNELS()       ("405 :You have joined too many channels") //405

#define ERR_NOSUCHNICK(client, nickname)        (RPL_HOST(client) + "401 " + nickname + " :No such nick/channel")       //405

#define ERR_NOPRIVILEGES(client)			(RPL_HOST(client) + "481 :Permission Denied- You're not an IRC operator")

#define ERR_UNKNOWNCOMMAND(command)    ("421 " + std::string(command) + " :Unknown command")          //421

//INFO
#define RPL_INFO(text)                  ("371 INFO: " + std::string(text))
#define RPL_ENDOFINFO()                 ("374 INFO: End of INFO list")  

// channel
#define ERR_CANNOTSENDTOCHAN(client, target)	(RPL_PREFIX(client) + "404 " + target + " :Cannot send to channel")
#define ERR_CHANOPRIVSNEEDED(target)	("482 " + target + " :You're not channel operator")
//HELP
#define ERR_HELPNOTFOUND(suject)        ("524 " + std::string(suject) + " :No help available on this topic")
#define RPL_HELPSTART(text)             ("704 :" + std::string(text))
#define RPL_INVITING(user, nick, channel)     ("341 " + user + " " + std::string(nick) + " " + std::string(channel))
#define S_INVITE(user, cible, channel)  (":" + user + " INVITE " + cible + " " + channel)
#define ERR_USERONCHANNEL(nick, channel) ("443 " + std::string(nick) + " " + std::string(channel) + " :is already on channel")
#define RPL_HELPTXT(text)               ("705 :" + std::string(text))
#define RPL_ENDOFHELP(text)             ("706 :" + std::string(text))

//VERSION
#define ERR_NOSUCHSERVER(servername)    ("402 " + std::string(servername) + " :No such server")
#define RPL_VERSION(version, server, comment)    ("351 " + std::string(version) + " " + std::string(server) + " :" + std::string(comment))

//TIME
#define RPL_TIME(server, time)   ("391 " + std::string(server) + " :" + std::string(time))

//LUSERS
#define RPL_LUSERCLIENT(users, invi, server)            ("251 :There are " + std::string(users) + " users and " + std::string(invi) + " invisible on " + std::string(server) + " servers")
#define RPL_LUSEROP(oper)                               ("252 " + std::string(oper) + " :operators online")

//TOPIC
#define RPL_NOTOPIC(channel)    ("331 " + channel + " :" + channel) 
#define RPL_TOPIC(channel, topic)    ("332 TOPIC " + channel + " " + topic ) 
#define RPL_TOPICWHOTIME(channel, nick, time)     ("333 " + channel + " " + channel + " " + nick + " " + std::string(time))

//NAMES
#define RPL_NAMREPLY(channel, symbol, names, username)    (":irc 353 " + username + " " + symbol + " " + channel + " :" + names)
#define RPL_ENDOFNAMES(channel, username)    (":irc 366 " + username + " " + channel + " :End of /NAMES list")

//MODE
#define ERR_UMODEUNKNOWNFLAG(target) ("501 " + std::string(target) =  " :Unknown MODE flag")

//JOIN	
#define ERR_NOSUCHCHANNEL(channel)  	("403 " + std::string(channel) + " :No such channel") 
#define ERR_NOTONCHANNEL(user, channel) ("451 " + user + " " + channel + " :You're not on that channel") 
#define ERR_BANNEDFROMCHAN(channel) 	("474 " + std::string(channel) + " :Cannot join channel (+b)")
#define ERR_BADCHANNELKEY(channel)  	("475 " + std::string(channel) + " :Cannot join channel (+k)")

