#pragma once

#include "../includes.hpp"

namespace irc { 
	/**
	 * @brief The Channel class stock all informations of a channel
	 * and has some utils for channel management
	 */
	class Channel {
		private:
			typedef std::list<User*>			ListUserChannel;
			typedef ListUserChannel::iterator	ListUserChannelIterator;


			std::string			_channelName;
			bool				_topicFlag;
			std::string			_topic;
			bool				_private;
			std::string			_password;
			int					_userLimit;

			Mods				_chanMods;
			ListUserChannel		_users;		
			ListUserChannel		_bans;		
			ListUserChannel		_operators;	     

			bool			checkPassword( std::string str );

		public:
			void		changeChanName( std::string name );
			void		changeUserLimit( int nb );
			void		changeChanTopic( std::string name );
			void		changeChanTopicFlag( void );
			void		changeChanTopicFlag(bool status);
			void		changePrivFlag(bool status );
			void		changePrivFlag(void);
			void		changeChanPassword( std::string password );
			void		sendMessage( std::string message );
			void		sendMessage( std::string message , User& user);
			void		sendMessageToOper( std::string message , User& user);
			//surement a remettre en privé (check puis utiliser la fction)


		//	Mods			*getMods();
			void		applyNewMods();
			void		inviteToChannel();
			// liste d invité?


			void		giveRights( User& guest );
			// comment gerer le fait de leave le channel : check si tjrs connecté? ou appel d une fct de deconnection
			void		joinChannel( User& user);
			void		addToOperatorList( User& user );
			void		addToBanList( User& user );  // if in channel => kik (fonction?)
			int			kick( User& user, bool rmBan = 0 );
			void		delFromOperatorList( User& user );
			void		delFromBansList( User& user );

			std::string 	getChannelName();  //
			std::string 	getChannelTopic();  //
			std::string 	getPassword(); //
			std::string		channelList( void );
			Mods		 	&getMods(); //
			bool		getPrivateBool(); //
			bool		isInChannel( std::string nickname );
			bool		isInBanList( std::string nickname );
			bool		isInOperatorList( std::string nickname );

			Channel( std::string name, bool privatebool, std::string password );
			Channel( std::string name );
			~Channel();

	};
}
