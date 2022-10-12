/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:16:56 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/11 01:49:39 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Parsing.hpp"
#include "includes.hpp"
#include <iostream>


#ifndef FT_TCP_PROTOCOL
// Protocol number of tcp protocol (less /etc/protocols)
# define FT_TCP_PROTOCOL 6
#endif

#ifndef FT_SOCK_BACKLOG
// Max of demand waiting on socket
# define FT_SOCK_BACKLOG 100
#endif

#ifndef FT_INET_ADDR
// ip match
# define FT_INET_ADDR "0.0.0.0"
#endif

namespace irc
{
	class Server 
	{
		private:
			typedef std::map<int, int>	map;
			typedef std::map<int, irc::Parsing>	mapParse;
			typedef std::pair<int, int>	pair_type;
			typedef map::iterator	map_iterator;

			u_int32_t			_port;
			std::string			_pwd;
			struct sockaddr_in	_sockAddr;
			int					_sockServ;
			map					_clients;
            mapParse            _Parse;

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
	};
} // namespace irc
