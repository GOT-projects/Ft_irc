/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:18:15 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/11 14:13:40 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../includes/Parsing.hpp"
#include <string>
#include <iostream>
#include <vector>
//Commande size max can be receive
#define MAX_CMD_LEN 512

using namespace irc;

Parsing::Parsing (const int fd, std::string &msg): _fd(fd), _msg(msg){
    //Add msg to buffer for handl CTRL-D
    _buffer.append(msg);
}

Parsing::~Parsing(){}

Parsing &Parsing::operator = (const Parsing &parsing){
    _fd = parsing._fd;
    _msg = parsing._msg;
    _buffer = parsing._buffer;
    _cmd = parsing._cmd;
    _cmds = parsing._cmds;
    return (*this);
}

Command::Command(std::string cmd, std::string prefix, std::vector<std::string> params)
: command(cmd), prefix(prefix), params(params){}
            

std::vector<std::string>  Parsing::splitMsg(const std::string &delimiter){
    std::vector<std::string>    result;
    std::string                 str = _buffer;
	size_t                      end;

    // first check 
    end = str.find(delimiter);
    if (end == std::string::npos)
        return (std::vector<std::string>());
    // save first command in vector
    if (end + delimiter.length() > MAX_CMD_LEN)
        throw std::runtime_error("Request too long");
    result.push_back(str.substr(0, end));
    
    // update str
    str.erase(0, end + delimiter.length());

    // loop for other commands
    end = str.find(delimiter);
    while (end != std::string::npos)
    {
        if (end + delimiter.length() > MAX_CMD_LEN)
            throw std::runtime_error("Request too long");
        result.push_back(str.substr(0, end));
        str.erase(0, end + delimiter.length());
        end = str.find(delimiter);
    }
	_buffer.clear();
	if (!str.empty())
	    _buffer = str;
    return (result);
}

void Parsing::splitCmds(std::vector<std::string> cmd_strings){
    std::vector<std::string>::iterator  it;
    size_t                              end;
    std::string                         prefix;

    for (it = cmd_strings.begin(); it != cmd_strings.end(); ++it)
    {
        // extract CMD name
        end = it->find(' ');
        if (end == std::string::npos) // only the command
        {
            if (it->find(':') == 0) // the only token is a prefix :'(
                throw std::runtime_error("IRC itage must have a command");
            _cmds.push_back(Command(it->substr(0, end)));
        }
        else // CMD + params
        {
            // CMD WITH PREFIX
            if (it->find(':') == 0)
            {
                prefix = it->substr(1, end);
                it->erase(0, end + 1);
                end = it->find(' ');
                if (end == std::string::npos)
                {
                    _cmds.push_back(Command(*it, prefix));
                    it->clear();
                }
                else
                {
                    _cmds.push_back(Command(it->substr(0, end), \
                                       prefix));
                    it->erase(0, end + 1);
                }
            }
            else // CMD WITH NO PREFIX
            { 
                _cmds.push_back(Command(it->substr(0, end)));
                end = it->find(' ');
                if (end == std::string::npos)
                    it->clear();
                else
                    it->erase(0, end + 1);
            }
            // PARAMS
            // TODO need check more about it
            if (!it->empty())
            {
                while (end != std::string::npos)
                {
                    // if long param starting with ":"
                    if (it->find(':') == 0)
                    {
                        _cmds.back().params.push_back(it->substr(1, \
                                                           it->length() - 1));
                        end = std::string::npos;
                    }
                    else
                    {
                        end = it->find(' ');
                        if (end == std::string::npos)
                            _cmds.back().params.push_back(*it);
                        else
                        {
                            _cmds.back().params
                                .push_back(it->substr(0, end));
                            it->erase(0, end + 1);
                        }
                    }
                }
            }
        }
    }
}

void	Parsing::displayCommands() {

	std::vector<Command>::iterator  it;
	std::vector<std::string>::iterator  it2;
    int i(0);
	for (it = _cmds.begin(); it < _cmds.end(); ++it)
	{
		std::cout << "\nPREFIX : " << it->prefix << std::endl;
		std::cout << "CMD : " << it->command << std::endl;
		for (it2 = it->params.begin(); it2 < it->params.end(); ++it2)
		{
			std::cout << "PARAM " << i++ << ": " << *it2 << std::endl;
		}
	}
}
