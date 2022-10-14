#pragma once

#include "includes.hpp"


// ** User
typedef std::list<irc::User>				listUser;
typedef listUser::iterator					listUserIterator;
typedef listUser::const_iterator			listUserConstIterator;
typedef std::map<int, irc::User>			mapUser;
typedef mapUser::iterator					mapUserIterator;
typedef mapUser::const_iterator				mapUserConstIterator;
typedef std::pair<int, irc::User>			pairUser;
// ** Parsing
typedef std::map<int, irc::Parsing>			mapParse;
typedef mapParse::iterator					mapParseIterator;
// ** Command
typedef void (*functionPtr)(irc::Server&, irc::User&, irc::Command&);
typedef std::map<std::string, functionPtr>	mapCommand;
typedef mapCommand::const_iterator			mapCommandConstIterator;
typedef std::pair<std::string, functionPtr>	pairCommand;


namespace irc
{
	class Server 
	{
		private:
			// Server infos
			u_int32_t			_port;
			std::string			_portString;
			std::string			_pwd;
			struct sockaddr_in	_sockAddr;
			int					_sockServ;
			const mapCommand	_commands;
			// User infos
			listUser			_onlineUsers;
			listUser			_offlineUsers;
			mapUser				_waitingUsers;
			mapParse			_Parse;
			// Debug
			Log					_log;

			void		createServer(void);
			void		runServer(void) const;
			void		acceptNewConnection(fd_set&	currentSocket, int& max_fd);
			void		handleClient(fd_set& currentSocket, const int fd, int& max_fd);
			void		killSocket(fd_set& currentSocket, const int fd, int& max_fd);

			static mapCommand	initCmd(void);
		public:
			Server(const std::string& port, const std::string& pwd);
			~Server(void);
			listUser&	getOnlineUsers();
			listUser&	getOfflineUsers();
			mapUser&	getWaitingUsers();
			void		connect(void);
            void    	SendClient(int fd, const std::string &msg);
			void    	display(void);
			User*		getUser(int fd);
	};
} // namespace irc











































































































































































































































































































































































