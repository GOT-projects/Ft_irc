/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 12:56:59 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/09 07:13:19 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/includes.hpp"
#include <functional>
#include <iostream>

std::string ConnectonSend(const irc::Parse &parse){
    irc::Parse::_s_connect info = parse.getInfo();
    std::string ret = ":127.0.0.1 001 ";
    ret.append(info.Nick);
    ret.append(" :");
    ret.append(WELCOME);
    ret.append(info.Nick);
    ret.append("!");
    ret.append(info.User);
    ret.append("@127.0.0.1\r\n");
    std::cout << ret << std::endl;
    return ret;
}

/* @Brief Parsing the command receive by the client 
   Pars and send to the differente cmd*/
/* @Param  fd_set& socket*/
/* @Param1  const int fd*/
/* @Param2  int &max_fd*/
/* @Return  void*/
void	ExecCmd(std::string& msg, const int fd) {
    irc::Parse pars(msg);
    std::string sendMsg;

    switch (pars.getCaseCmd()) {
        case CONNECT:
            sendMsg = ConnectonSend(pars);
            send(fd, sendMsg.c_str(), sendMsg.length(), O_NONBLOCK);
        case PING:
            send(fd, "PONG", 3, O_NONBLOCK);
    }
    std::cout << pars;
    std::cout << "fd " << fd << " receive: " << msg;
    std::cout << YELLOW << "Client with the socket " << fd << " receive :" << NC << std::endl;
    std::cout << msg << YELLOW_BK << "END OF RECEPTION" << NC << "\n\n" << std::endl;
}

