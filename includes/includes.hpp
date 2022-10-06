/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges jmilhas rcuminal <x@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 00:48:53 by aartiges jm       #+#    #+#             */
/*   Updated: 2022/10/06 02:16:38 by aartiges jm      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define DEBUG true

// c++
#include <iostream>
#include <string>
#include <cstdint>
#include <exception>
#include <stdexcept>
//#include <algorithm>

// Réseau
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>

#include <errno.h>
//#include <cstring>
//#include <iterator>
//#include <ostream>
//#include <vector>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <iomanip>
//#include <sstream>

// Our code

#include "server.hpp"