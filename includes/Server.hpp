#pragma once

#include "includes.hpp"

namespace irc
{
	class Server 
	{
		private:
			typedef std::map<int, int>		map;
			typedef std::map<int, Parsing>	mapParse;
			typedef std::pair<int, int>		pair_type;
			typedef map::iterator			map_iterator;

			u_int32_t			_port;
			std::string			_portString;
			std::string			_pwd;
			struct sockaddr_in	_sockAddr;
			int					_sockServ;
			map					_clients;
			mapParse			_Parse;
            Log                 _log;

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
