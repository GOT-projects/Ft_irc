#pragma once

#include "../includes.hpp"

namespace irc
{

class Server;

/**
 * @brief Have all information of a user and allow to send a message
 * at the user
 */
class User
{
	private:
		int			_socketFd;
		std::string	_username; // unique
		std::string	_nickname; // pseudo
		std::string	_realname; // visual
		std::string	_hostname;
		std::string	_servername;
		UserMode	_mode;
	public:
		User(void);
		User(int fd);
		~User(void);

		// getter

		int			getSocketFd(void) const;
		std::string	getUsername(void) const;
		std::string	getNickname(void) const;
		std::string	getRealname(void) const;
		std::string	getHostname(void) const;
		std::string	getServername(void) const;
		// getter modes

		bool	isInvisible(void) const;
		bool	isServerNotice(void) const;
		bool	isWallOps(void) const;
		bool	isOperatorServer(void) const;


		// setter

		void	setSocketFd(const int socketFd);
		void	setUsername(const std::string& val);
		void	setNickname(const std::string& val);
		void	setRealname(const std::string& val);
		void	setHostname(const std::string& val);
		void	setServername(const std::string& val);
		// setter modes

		void	beInvisible(const bool boolean);
		void	beServerNotice(const bool boolean);
		void	beWallOps(const bool boolean);
		void	beOperatorServer(const bool boolean);
		// utility

		int		sendCommand(const std::string& command) const;
}; // class User
} // namespace irc


