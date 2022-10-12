/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmilhas <jmilhas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 00:27:40 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/13 00:27:48 by jmilhas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// c++
#include <iostream>
#include <string>
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
#include <iomanip>

// Utils
#include <stdlib.h>

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
#include "utils/string.hpp"
#include "Parsing.hpp"
#include "user/UserMode.hpp"
#include "user/User.hpp"
#include "channel/ChannelMode.hpp"
#include "channel/Channel.hpp"
#include "Server.hpp"
