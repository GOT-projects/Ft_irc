#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief Function that comapare 2 users by nickname and username
	 * 
	 * @param us1 an user
	 * @param us2 an user
	 * @return u_int8_t 0 if not equivalent, EXIST_IN if same instance,
	 * EXIST_IN_COPY if same but not the same instance
	 */
	u_int8_t	isSameUser(const User& us1, const User& us2) {
		if (&us1 == &us2)
			return (EXIST_IN);
		if (
			us1.getNickname() == us2.getNickname()
			&&
			us1.getUsername() == us2.getUsername()
		)
			return (EXIST_IN_COPY);
		return 0;
	}

	/**
	 * @brief Function that comapare 2 users by nickname
	 * 
	 * @param us1 an user
	 * @param us2 an user
	 * @return u_int8_t 0 if not equivalent, EXIST_IN if same instance,
	 * EXIST_IN_COPY if same but not the same instance
	 */
	u_int8_t	isSameNickname(const User& us1, const User& us2) {
		if (&us1 == &us2)
			return (EXIST_IN);
		if (us1.getNickname() == us2.getNickname())
			return (EXIST_IN_COPY);
		return 0;
	}

	/**
	 * @brief Function that comapare 2 users by username
	 * 
	 * @param us1 an user
	 * @param us2 an user
	 * @return u_int8_t 0 if not equivalent, EXIST_IN if same instance,
	 * EXIST_IN_COPY if same but not the same instance
	 */
	u_int8_t	isSameUsername(const User& us1, const User& us2) {
		if (&us1 == &us2)
			return (EXIST_IN);
		if (us1.getUsername() == us2.getUsername())
			return (EXIST_IN_COPY);
		return 0;
	}

	u_int8_t	isSameSocket(const User& us1, const User& us2) {
		if (&us1 == &us2)
			return (EXIST_IN);
		if (us1.getSocketFd() == us2.getSocketFd())
			return (EXIST_IN_COPY);
		return 0;
	}

	/**
	 * @brief Check if a user is in a list of users
	 * 
	 * @param user the user to compare
	 * @param users the list of users
	 * @param fun function to compare users
	 * @return u_int8_t (binary operation)
	 * 
	 * if user instance is in the list returnValue | EXIST_IN will be != 0
	 * 
	 * if user copy is in the list returnValue | EXIST_IN_COPY will be != 0
	 */
	u_int8_t	isInList(User& user, listUser& users, funCompareUser fun) {
		u_int8_t	ret = 0;
		for (listUserConstIterator it = users.begin(); it != users.end(); it++) {
			ret |= (*fun)(*it, user);
		}
		return ret;
	}

	/**
	 * @brief Check if a user is in a map of users
	 * 
	 * @param user the user to compare
	 * @param users the map of users
	 * @param fun function to compare users
	 * @return u_int8_t (binary operation)
	 * 
	 * if user instance is in the map returnValue | EXIST_IN will be != 0
	 * 
	 * if user copy is in the map returnValue | EXIST_IN_COPY will be != 0
	 */
	u_int8_t	isInMap(User& user, mapUser& users, funCompareUser fun) {
		u_int8_t	ret = 0;
		for (mapUserConstIterator it = users.begin(); it != users.end(); it++) {
			ret |= (*fun)(it->second, user);
		}
		return ret;
	}

	/**
	 * @brief Disconnect a user (fd = -1) and return iterator
	 * 
	 * @param fd file descriptor of the connected user
	 * @param users list of users
	 * @return listUserIterator an iterator, if returnValue is users.end()
	 * then the user is not in the list
	 */
	listUserIterator	disconnectUserIn(const int fd, listUser& users) {
		listUserIterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if (it->getSocketFd() == fd) {
				it->setSocketFd(-1);
				return (it);
			}
		}
		return it;
	}

	/**
	 * @brief Get the User In List object
	 * 
	 * @param fd file descriptor of the connected user
	 * @param users list of users
	 * @param fun function to compare users
	 * @return User* a pointer on the user
	 * 
	 * if NULL then the user is not in the list
	 */
	User*	getUserInList(const User& user, listUser& users, funCompareUser fun) {
		listUserIterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if ((*fun)(user, *it))
				return (&(*it));
		}
		return NULL;
	}

	/**
	 * @brief Get the User Iterator In List of user
	 * 
	 * @param user the user to compare
	 * @param users the list of user
	 * @param fun function to compare users
	 * @return listUserIterator on user of the list which match the fun
	 */
	listUserIterator	getUserIteratorInList(const User& user, listUser& users, funCompareUser fun) {
		listUserIterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if ((*fun)(user, *it))
				return (it);
		}
		return it;
	}

	/**
	 * @brief Get the User Iterator In Map of user
	 * 
	 * @param user the user to compare
	 * @param users the map of user
	 * @param fun function to compare users
	 * @return mapUserIterator on user of the map which match the fun
	 */
	mapUserIterator		getUserIteratorInMap(const User& user, mapUser& users, funCompareUser fun) {
		mapUserIterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if ((*fun)(it->second, user))
				return it;
		}
		return it;
	}
} // namespace irc

