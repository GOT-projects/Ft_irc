/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 14:50:44 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/09 07:47:40 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/includes.hpp"
#include <_ctype.h>
#include <regex>
#include <string>

using namespace irc;

Parse::Parse(std::string& msg){
    std::vector<std::string> cmd;
    _connect = false;
    _caseCmd = -1;
    msg = ReplaceSpecialChar(msg);
    cmd = SplitCmd(msg, ':');
    ParseCmd(cmd);

    AddCase();
}

/* @Brief Check string and replace \r \n of the string*/
/* @Param  std::String msg*/
/* @Return  std::String msg*/
std::string    Parse::ReplaceSpecialChar(std::string &msg){
    // Remove newline characters from string in C++
    msg = std::regex_replace(msg, std::regex("\\r\\n|\\r|\\n"), " ");
    return msg;
}

std::vector<std::string> Parse::SplitCmd(std::string &msg, const char sep){
    std::vector<std::string> cmd;
    size_t start;
    size_t end = 0;

    while ((start = msg.find_first_not_of(sep, end)) != std::string::npos){
        end = msg.find(sep, start);
        cmd.push_back(msg.substr(start, end - start));
    }
    std::cout << "Print Pars Cmd: " << std::endl;
    for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++){
        std::cout << "\t" << *it << std::endl;
    }
    return cmd;
}

void Parse::AddCase(){
    if (_connect){
        _caseCmd = CONNECT;
    }else if (_cmd[0] == "PING"){
        std::cout << "Ping active" << std::endl;
        _caseCmd = PING;
    }else if (_cmd[0] == "JOIN"){
        _caseCmd = JOIN;
    }

}

void Parse::ParseCmd(std::vector<std::string> &cmd){
    std::string regex;
    std::regex reCmd("[A-Z][\\w]+[ ]");
    std::vector<std::string> info;
    std::sregex_iterator iter(cmd[0].begin(), cmd[0].end(), reCmd);

    const std::sregex_iterator end ;
    for(  ; iter != end ; ++iter ){ 
        /* std::cout << iter->str() <<  '\n'; */
        _cmd.push_back(std::regex_replace(iter->str(), std::regex(" "), "\0"));
    }
    if (_cmd.size() == 2 && _cmd[0] == "NICK" && _cmd[1] == "USER"){
        _connect = true;
        info = SplitCmd(cmd[0], ' ');
        _UserInfo.Nick = info[1];
        _UserInfo.User = info[3];
        _UserInfo.Arg1 = info[4];
        _UserInfo.Arg2 = info[5];
    }else if (_cmd[0] == "JOIN"){
        info = SplitCmd(cmd[0], ' ');
        _cmd.push_back(std::regex_replace(info[1], std::regex(" "), "\0"));
    }
}

Parse::_s_connect Parse::getInfo(void)const{
    return (_UserInfo);
}

std::vector<std::string> Parse::getCmd(void)const{
    return (_cmd);
}
 std::vector<std::string> Parse::getUser(void)const{
    return (_user);
}
std::string Parse::getContent(void)const{
    return (_content);
}

int Parse::getCaseCmd(void)const{
    return (_caseCmd);
}
std::ostream & operator <<(std::ostream &o, Parse const &parse){
    std::vector<std::string> info = parse.getUser();
    std::vector<std::string> cmd = parse.getCmd();
	o << "cmd:";
    for (std::vector<std::string>::iterator it = cmd.begin(); it != cmd.end(); it++){
	    o << "\n\t" << *it;
    }

	o << "\ninfo:";
    for (std::vector<std::string>::iterator it = info.begin(); it != info.end(); it++){
	    o << "\n\t" << *it;
    } 
	o << "\ncontente:\n\t" << parse.getContent() << std::endl;
	return (o);
}
