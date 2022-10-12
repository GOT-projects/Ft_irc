/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges jmilhas rcuminal <x@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:16:47 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/12 22:18:05 by aartiges jm      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "includes.hpp"

namespace irc
{
    struct Command
    {
        std::string                 command;
        std::string                 prefix;
        std::vector<std::string>    params;
    
        Command(std::string cmd, std::string prefix = std::string(), \
                std::vector<std::string> params = std::vector<std::string>());
    };

	class Parsing
	{
		private:
            int _fd;
            std::string _msg;
            std::string _buffer;
            std::vector<std::string> _cmd;
            std::vector<Command>        _cmds;

		public:
			Parsing(const int fd, std::string &msg);
			Parsing(){};
			~Parsing(void);

            Parsing &operator = (const Parsing &parsing);
            std::vector<std::string>  splitMsg(const std::string &delimiter);
            void  splitCmds(std::vector<std::string> cmd_strings);
            void	displayCommands();
	};
} // namespace irc
