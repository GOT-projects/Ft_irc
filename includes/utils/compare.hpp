#pragma once

#include "../includes.hpp"

typedef u_int8_t (*funCompareUser)(const irc::User&, const irc::User&);

namespace irc
{
	/**
	 * @brief All functions here, are for research / compare
	 */

	u_int8_t			isSameUser(const User& us1, const User& us2);
	u_int8_t			isSameNickname(const User& us1, const User& us2);
	u_int8_t			isSameUsername(const User& us1, const User& us2);
	u_int8_t			isSameSocket(const User& us1, const User& us2);

	u_int8_t			isInList(User& user, listUser& users, funCompareUser fun);
	u_int8_t			isInMap(User& user, mapUser& users, funCompareUser fun);

	listUserIterator	disconnectUserIn(int fd, listUser& users);
	User*				getUserInList(const User& user, listUser& users, funCompareUser fun);
	listUserIterator	getUserIteratorInList(const User& user, listUser& users, funCompareUser fun);
	mapUserIterator		getUserIteratorInMap(const User& user, mapUser& users, funCompareUser fun);
} // namespace irc
