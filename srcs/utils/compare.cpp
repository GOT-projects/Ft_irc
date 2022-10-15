#include "../../includes/includes.hpp"

namespace irc
{
	/**
	 * @brief Check if a user is in a list of users
	 * 
	 * @param user the user to compare
	 * @param users the list of users
	 * @return u_int8_t (binary operation)
	 * 
	 * if user instance is in the list returnValue | EXIST_IN will be != 0
	 * 
	 * if user copy is in the list returnValue | EXIST_IN_COPY will be != 0
	 */
	u_int8_t	isInList(User& user, listUser& users) {
		u_int8_t	ret = 0;
		for (listUserConstIterator it = users.begin(); it != users.end(); it++) {
			if (&(*it) == &user)
				ret |= EXIST_IN;
			else if (it->getNickname() == user.getNickname())
				ret |= EXIST_IN_COPY;
		}
		return ret;
	}

	/**
	 * @brief Check if a user is in a map of users
	 * 
	 * @param user the user to compare
	 * @param users the map of users
	 * @return u_int8_t (binary operation)
	 * 
	 * if user instance is in the map returnValue | EXIST_IN will be != 0
	 * 
	 * if user copy is in the map returnValue | EXIST_IN_COPY will be != 0
	 */
	u_int8_t	isInMap(User& user, mapUser& users) {
		u_int8_t	ret = 0;
		for (mapUserConstIterator it = users.begin(); it != users.end(); it++) {
			if (&(it->second) == &user)
				ret |= EXIST_IN;
			else if (it->second.getNickname() == user.getNickname())
				ret |= EXIST_IN_COPY;
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
	 * @return User* a pointer on the user
	 * 
	 * if NULL then the user is not in the list
	 */
	User*	getUserInList(const int fd, listUser& users) {
		listUserIterator it;
		for (it = users.begin(); it != users.end(); it++) {
			if (it->getSocketFd() == fd) {
				return (&(*it));
			}
		}
		return NULL;
	}
} // namespace irc

