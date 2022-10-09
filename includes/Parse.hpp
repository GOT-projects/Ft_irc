/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:49:29 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/09 07:11:58 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once

#include "includes.hpp"

namespace irc
{
	class Parse
	{
        public:
            struct _s_connect{
                std::string Nick;
                std::string User;
                std::string Arg1;
                std::string Arg2;
            };
		private:
			typedef std::vector<std::string>    vector;
            vector                              _cmd;
            vector                              _user;
            std::string                         _content;
            int                                 _caseCmd;
            bool                                _connect;
            _s_connect                          _UserInfo;

		public:
			Parse(std::string& msg);
			~Parse(void){std::cout << "Destructor Parse" << std::endl;};
            vector getCmd(void)const;
            vector getUser(void)const;
            int getCaseCmd(void)const;
            _s_connect getInfo(void)const;
            std::string getContent(void)const;
            void AddCase();

        private:
            std::string    ReplaceSpecialChar(std::string &msg);
            vector SplitCmd(std::string &msg, const char sep);
            void ParseCmd(std::vector<std::string> &cmd);
	};
} // namespace irc
    std::ostream & operator <<(std::ostream &o, irc::Parse const &parse);
