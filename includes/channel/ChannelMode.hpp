#pragma once

#include "../includes.hpp"

namespace irc { 
	/**
	 * @brief Class that represente the modes of a channel
	 */
	class Mods {
		public:
			bool	_secretChannel;
			bool	_privateChannel;
			bool	_inviteOnly;
			bool	_nameTopicByOper;
			int		_maxUsers;


			//o - give/take channel operator privileges;
			//k - set a channel key (password).

			Mods(){
				_secretChannel = false;
				_privateChannel = false;
				_inviteOnly = false;
				_nameTopicByOper = false;
				_maxUsers = 0;
			};
			~Mods(){};
	};
}
