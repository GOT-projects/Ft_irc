#pragma once

#include "includes.hpp"

#ifndef FT_TCP_PROTOCOL
// Protocol number of tcp protocol (less /etc/protocols)
# define FT_TCP_PROTOCOL 6
#endif

#ifndef FT_SOCK_BACKLOG
// Max of demand waiting on socket
# define FT_SOCK_BACKLOG 100
#endif

#ifndef FT_INET_ADDR
// Max of demand waiting on socket
# define FT_INET_ADDR "127.0.0.1"
#endif

namespace irc
{
	class Server
	{
		private:
			typedef std::map<int, int>	map;
			typedef std::pair<int, int>	pair_type;
			typedef map::iterator	map_iterator;

			u_int32_t			_port;
			std::string			_pwd;
			struct sockaddr_in	_sockAddr;
			int					_sockServ;
			map					_clients;

			void	createServer(void);
			void	runServer(void) const;
			void	acceptNewConnection(fd_set&	currentSocket, int& max_fd);
			void	handleClient(fd_set& currentSocket, const int fd, int& max_fd);
			void	killSocket(fd_set& currentSocket, const int fd, int& max_fd);
		public:
			Server(const std::string& port, const std::string& pwd);
			~Server(void);
			void	connect(void);
	};
} // namespace irc
