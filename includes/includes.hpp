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

// c++
#include <iostream>
#include <string>
// #include <cstdint> // FIXME c++11
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <map>
#include <list>

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

#include "Server.hpp"
#include "user/UserMode.hpp"
#include "user/User.hpp"