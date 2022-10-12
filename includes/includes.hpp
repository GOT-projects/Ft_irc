/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges jmilhas rcuminal <x@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:16:07 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/12 22:28:31 by aartiges jm      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// c++
#include <iostream>
#include <string>
// #include <cstdint> // FIXME c++11
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <list>
#include <vector>

// Réseau
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

// Error
#include <errno.h>
#include <string.h>

//#include <cstring>
//#include <iterator>
//#include <ostream>
//#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <iomanip>
//#include <sstream>

// Our code

#include "define.hpp"
#include "Parsing.hpp"
#include "user/UserMode.hpp"
#include "user/User.hpp"
#include "channel/ChannelMode.hpp"
#include "channel/Channel.hpp"
#include "Server.hpp"
