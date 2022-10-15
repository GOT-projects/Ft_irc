#pragma once

#include "../includes.hpp"

namespace irc { 
	/**
	 * @brief Class that represente the modes of a channel
	 */
	class Mods {
		public:
			bool	_secretChannel;			//s - secret channel flag;
			bool	_inviteOnly;			//i - invite-only channel flag;
			bool	_nameTopicByOper;		//t - topic settable by channel operator only flag;

			void	operPrivileges();		//o - give/take channel operator privileges;
			void	setChannelPassword();	//k - set a channel key (password).
				
			//When using the 'o' and 'b' options, a restriction on a total of three
			//per mode command has been imposed.  That is, any combination of 'o'
			//and
	};
}
