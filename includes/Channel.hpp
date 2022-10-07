#pragma once

#include "includes.hpp"

namespace irc { 
	class Channel {
		private:
				std::string		_channelName;
				bool			_private;
				// Map des utilisateurs
				// Map des moderateurs
				// Map des channels
				
		public:
				Channel() {};
				~Channel() {};

	};
}


