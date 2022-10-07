/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges jmilhas rcuminal <x@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:57:08 by aartiges jm       #+#    #+#             */
/*   Updated: 2022/10/06 03:10:01 by aartiges jm      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

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
		public:
			Server(const std::string& port, const std::string& pwd);
			~Server();
			void	connect();
	};
} // namespace irc
