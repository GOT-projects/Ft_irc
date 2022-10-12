/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:16:47 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/11 01:49:04 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include <string>
#include <vector>

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
