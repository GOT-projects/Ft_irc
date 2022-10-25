#pragma once

#include "../includes.hpp"

namespace irc
{
	/**
	 * @brief Class log for server logs like print time ...
	 */
	class Log
	{
		private:
			std::string	_log;
			time_t		_now;
			std::tm		*_ltm;

		public:
			Log();
			~Log(void);
			void initLog();
			std::tm *getTm();
			std::string getTime();
	};
} // namespace irc
std::ostream & operator<< (std::ostream &o, irc::Log &log);
