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
			void	changeTopicFlag(bool status);
			void	changeSecretFlag( void );
			void	changeSecretFlag(bool status);
			void	changeInviteFlag( void );
			void	changeInviteFlag(bool status);

			Mods( void ){
				_secretFlag = false;
				_inviteOnly = false;
				_topicFlag = false;
			};
			~Mods(){};
	};
}
