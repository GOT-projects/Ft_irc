#pragma once

#include "../includes.hpp"

using namespace irc;

class UserMode
{
	private:
		bool	_invisible;
		bool	_serverNotice;
		bool	_wallOps;
		bool	_operatorServer;
	public:
		UserMode(void);
		~UserMode(void);
		// getter
		bool	getInvisible(void) const;
		bool	getServerNotice(void) const;
		bool	getWallOps(void) const;
		bool	getOperatorServer(void) const;
		//setter
		void	setInvisible(const bool boolean);
		void	setServerNotice(const bool boolean);
		void	setWallOps(const bool boolean);
		void	setOperatorServer(const bool boolean);
	}; // class UserMode

