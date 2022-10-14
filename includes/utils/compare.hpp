#pragma once

#include "../includes.hpp"

namespace irc
{
	u_int8_t			isInList(User& user, listUser& users);
	u_int8_t			isInMap(User& user, mapUser& users);
	listUserIterator	disconnectUserIn(int fd, listUser& users);
	User*				getUserInList(const int fd, listUser& users);
} // namespace irc
