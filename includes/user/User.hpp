#pragma once

#include "../includes.hpp"

using namespace irc;

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
		~User(void);
		// getter
		int			getSocketFd(void) const;
		std::string	getUsername(void) const;
		std::string	getNickname(void) const;
		std::string	getRealname(void) const;
		std::string	getHostname(void) const;
		std::string	getServername(void) const;
		bool	isInvisible(void) const;
		bool	isServerNotice(void) const;
		bool	isWallOps(void) const;
		bool	isOperatorServer(void) const;
		// setter
		void	setSocketFd(const int socketFd);
		void	getUsername(const std::string& val);
		void	getNickname(const std::string& val);
		void	getRealname(const std::string& val);
		void	getHostname(const std::string& val);
		void	getServername(const std::string& val);
		void	beInvisible(const bool boolean);
		void	beServerNotice(const bool boolean);
		void	beWallOps(const bool boolean);
		void	beOperatorServer(const bool boolean);
		// utility
		int	sendCommand(const std::string& command) const;
}; // class User
