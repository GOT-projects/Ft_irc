#include "../../includes/includes.hpp"
#include <string>

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
        for (listUserIterator it = user.begin(); it != user.end(); ++it){
            if (it->isOperatorServer())
                i++;
        }
        return std::to_string(i);
    }

	/**
	 * @brief apply command LUSERS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	LUSERS(Server& serv, User& user, Command& ) {
		if (!user.getCap()) {
			std::cerr << RED << serv.getLog() << "LUSERS: Cap error" << NC << std::endl;
			user.sendCommand(":please set cap to 302");
			return;
		}else if (!user.getPass() || !isRegister(user)) {
			std::cerr << RED << serv.getLog() << "LUSERS: password required / register need" << NC << std::endl;
			user.sendCommand(":register need / password");
			return;
        }else{
            /* serv.getOnlineUsers().size() */
            user.sendCommand(RPL_LUSERCLIENT(std::to_string(serv.getOnlineUsers().size()), "0", "ft_irc"));
            user.sendCommand(RPL_LUSEROP(getOperator(serv.getOnlineUsers())));
        }
    };
}//namespace irc
