#include "../../includes/includes.hpp"

using namespace irc;

User::User(int fd)
: _socketFd(fd), _username(""), _nickname(""), _realname(""), _hostname(""),
_servername(""), _mode(UserMode())
{}


User::User(void)
: _socketFd(-1), _username(""), _nickname(""), _realname(""), _hostname(""),
_servername(""), _mode(UserMode())
{}
User::~User(void) {}
// getter
int			User::getSocketFd(void) const {return _socketFd;}
std::string	User::getUsername(void) const {return _username;}
std::string	User::getNickname(void) const {return _nickname;}
std::string	User::getRealname(void) const {return _realname;}
std::string	User::getHostname(void) const {return _hostname;}
std::string	User::getServername(void) const {return _servername;}

bool		User::isInvisible(void) const {return _mode.getInvisible();}
bool		User::isServerNotice(void) const {return _mode.getServerNotice();}
bool		User::isWallOps(void) const {return _mode.getWallOps();}
bool		User::isOperatorServer(void) const {return _mode.getOperatorServer();}


// setter
void		User::setSocketFd(const int socketFd) {_socketFd = socketFd;}
void		User::setUsername(const std::string& val) {_username = val;}
void		User::setNickname(const std::string& val) {_nickname = val;}
void		User::setRealname(const std::string& val) {_realname = val;}
void		User::setHostname(const std::string& val) {_hostname = val;}
void		User::setServername(const std::string& val) {_servername = val;}

void		User::beInvisible(const bool boolean) {_mode.setInvisible(boolean);}
void		User::beServerNotice(const bool boolean) {_mode.setServerNotice(boolean);}
void		User::beWallOps(const bool boolean) {_mode.setWallOps(boolean);}
void		User::beOperatorServer(const bool boolean) {_mode.setOperatorServer(boolean);}


// utility
int			User::sendCommand(const std::string& command) const {
	if (_socketFd == -1) {
		std::cout << RED << "Send to user fail - no client" << NC << std::endl;
		return 1;
	}
	send(_socketFd, command.c_str(), command.size(), O_NONBLOCK);
	return 0;
}
