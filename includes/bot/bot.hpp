#pragma once

#include "../includes.hpp"
#include <string>

namespace irc
{
	/**
	 * @brief Class Bot Backlist word PriveMsg
	 */
	class Bot
	{
		public:
		typedef std::map<std::string, int> mapBot;

		private:
			mapBot 	_blacklist;

		public:
			Bot();
			~Bot(void);
			std::string blacklistMsg(std::string &msg)const ;
	};
} // namespace irc
