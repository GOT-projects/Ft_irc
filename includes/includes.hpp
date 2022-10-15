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
#include <stdio.h>
#include <ctime>

// Error
#include <errno.h>
#include <string.h>

// Our code

#include "define.hpp"
#include "log/log.hpp"
#include "utils/string.hpp"
#include "Parsing.hpp"
#include "user/UserMode.hpp"
#include "user/User.hpp"
#include "channel/ChannelMode.hpp"
#include "channel/Channel.hpp"
#include "Server.hpp"
#include "utils/compare.hpp"
#include "commands.hpp"
#include "reply.hpp"
