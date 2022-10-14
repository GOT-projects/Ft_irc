#include "../../includes/includes.hpp"

namespace irc
{
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

