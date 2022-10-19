#pragma once

#include "../includes.hpp"

namespace irc { 
	/**
	 * @brief Class that represente the modes of a channel
	 */
	class Mods {
		public:
			bool	_topicFlag;
			bool	_secretFlag;
			bool	_inviteOnly;
		//	int		_maxUsers;

			void	changeTopicFlag( void );
			void	changeSecretFlag( void );
			void	changeInviteFlag( void );

			Mods( void ){
				_secretFlag = false;
				_inviteOnly = false;
				_topicFlag = false;
			};
			~Mods(){};
	};
}
