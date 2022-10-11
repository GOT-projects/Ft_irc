/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:16:07 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/11 00:17:23 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define DEBUG		true
#define RED			"\033[0;31m"
#define RED_ERR		"\033[1;41m"
#define GREEN		"\033[1;32m"
#define YELLOW		"\033[1;33m"
#define YELLOW_BK	"\033[1;43m"
#define BLUE		"\033[1;34m"
#define BLUE_BK		"\033[1;44m"
#define NC			"\033[0m"


//Commande size max can be receive
#define MAX_CMD_LEN 512

// c++
#include <iostream>
#include <string>
#include <cstdint>
#include <exception>
#include <stdexcept>
#include <map>
#include <algorithm>
#include <sys/_types/_ssize_t.h>

// Réseau
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

#include <errno.h>
//#include <cstring>
//#include <iterator>
//#include <ostream>
//#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <iomanip>
//#include <sstream>

// Our code

