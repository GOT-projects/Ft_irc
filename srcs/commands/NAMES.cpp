#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief apply command PASS
	 * 
	 * @param serv server
	 * @param user user who send request
	 * @param cmd command
	 */
	void	NAMES(Server& serv, User& user, Command& cmd) {
		if (cmd.params.size() < 1) {
			std::cout << RED << serv.getLog() << "NAMES: ERR_NEEDMOREPARAMS " << NC << std::endl;
			user.sendCommand(ERR_NEEDMOREPARAMS("NAMES"));
			return;
		}
		if (cmd.params.size() > 2) {
			std::cerr << RED << serv.getLog() << "NAMES: ERR_toomuchPARAMS " << NC << std::endl;
			return;
		}
        if (cmd.params.size() == 1) {
            for (mapChannelIterator it = serv.getMapChannel().begin(); it != serv.getMapChannel().begin(); it++){
                if (!it->second.getMods()._secretFlag && !it->second.getPrivateBool() && !it->second.isInBanList(user.getNickname()))
                    std::cout << "voici la liste des users du channel\n"; // printf list;   RPL_NAMREPLY       RPL_ENDOFNAMES
            }
        }
        if (cmd.params.size() == 2) {
            for (mapChannelIterator it = serv.getMapChannel().begin(); it != serv.getMapChannel().begin(); it++){
                if (!it->second.getMods()._secretFlag && !it->second.getPrivateBool() && !it->second.isInBanList(user.getNickname()))
                    std::cout << "voici la liste des users du channel\n"; // printf list;   RPL_NAMREPLY       RPL_ENDOFNAMES
            }
        }
	}
}
