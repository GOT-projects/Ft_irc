#pragma once

#include "includes.hpp"

namespace irc
{
	/**
	 * @brief A command parsed
	 */
	struct Command
	{
		std::string					command;
		std::string					prefix;
		std::vector<std::string>	params;
		
		Command(std::string cmd, std::string prefix = std::string(), \
				std::vector<std::string> params = std::vector<std::string>());
	};

	/**
	 * @brief Class used for parsing
	 */
	class Parsing
	{
		typedef std::vector<Command>		vectorCmd;
		typedef std::vector<std::string>	vectorString;
		private:
			int							_fd;
			bool						_completed;
			bool						_readyTosend;
			std::string					_msg;
			std::string					_buffer;
			vectorString				_cmd;
			vectorCmd					_cmds;

		public:
			Parsing(const int fd);
			Parsing(){};
			~Parsing(void);

			Parsing			&operator = (const Parsing &parsing);
			vectorString	splitMsg(std::string &msg, const std::string &delimiter);
			void			splitCmds(std::vector<std::string> cmd_strings);
			bool			getCompleted()const;
			void			setReadyToSend(bool b);
			void			ClearCommand();
			bool			getReadyToSend(void)const;
			
			vectorCmd		getCommand()const;
			void			displayCommands();
			Command*		getNextCmd();

		private:
			void			_tolowerCmd();
			void			_RemoveEmptyCmd();

	};
} // namespace irc
