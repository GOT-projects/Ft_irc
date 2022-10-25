#include "../../includes/includes.hpp"
#include <sstream>

namespace irc
{
	/**
	 * @brief get nunber of operator connect
	 * 
	 * @param list user
	 * return string;
	 */
	static std::string getOperator(listUser user){
		int i(0);
		std::stringstream ss;
		for (listUserIterator it = user.begin(); it != user.end(); ++it){
			if (it->isOperatorServer())
				i++;
		}
		ss << i;
		return ss.str();
	}

	/**
	 * @brief apply command LUSERS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	LUSERS(Server& serv, User& user, Command& ) {
		std::stringstream ss;
		
		/* serv.getOnlineUsers().size() */
		ss << serv.getOnlineUsers().size();
		user.sendCommand(RPL_LUSERCLIENT(ss.str(), "0", "ft_irc"));
		user.sendCommand(RPL_LUSEROP(getOperator(serv.getOnlineUsers())));
	};
}//namespace irc
