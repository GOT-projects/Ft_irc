#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command QUIT
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	QUIT(Server& serv, User& user, Command& ) {
        //TODO need remove user inside all channel and remove from Userlist
        //not need return any message
    };
}//namespace irc
