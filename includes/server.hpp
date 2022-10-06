/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges jmilhas rcuminal <x@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:57:08 by aartiges jm       #+#    #+#             */
/*   Updated: 2022/10/06 01:54:19 by aartiges jm      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "includes.hpp"

namespace irc
{
	class Server
	{
		private:
			u_int32_t			_port;
			std::string			_pwd;
			struct sockaddr_in	_sockAddr;
			int					_sockServ;
		public:
			Server(const std::string& port, const std::string& pwd);
			~Server();
			void	connect();
	};
} // namespace irc
