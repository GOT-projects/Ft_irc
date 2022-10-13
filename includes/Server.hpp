#pragma once

#include "includes.hpp"

namespace irc
{
	class Server 
	{
		private:
			typedef std::list<User>			listUser;
			typedef listUser::iterator		listUserIterator;
			typedef std::map<int, Parsing>	mapParse;
			typedef mapParse::iterator		mapParseIterator;

			// Server infos
			u_int32_t			_port;
			std::string			_portString;
			std::string			_pwd;
			struct sockaddr_in	_sockAddr;
			int					_sockServ;
			// User infos
			listUser			_onlineUser;
			listUser			_offlineUser;
			mapParse			_Parse;
			// Debug
			Log					_log;

			void	createServer(void);
			void	runServer(void) const;
			void	acceptNewConnection(fd_set&	currentSocket, int& max_fd);
			void	handleClient(fd_set& currentSocket, const int fd, int& max_fd);
			void	killSocket(fd_set& currentSocket, const int fd, int& max_fd);
		public:
			Server(const std::string& port, const std::string& pwd);
			~Server(void);
			void	connect(void);
            void    SendClient(int fd, const std::string &msg);
			void    display(void);
	};
} // namespace irc
