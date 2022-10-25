#include "../../includes/includes.hpp"

using namespace irc;

/**
 * @brief Construct a new User:: User object
 * 
 * @param fd file descriptor of client
 */
User::User(int fd)
: _socketFd(fd), _username(""), _nickname(""), _realname(""), _hostname("irc"),
_servername("irc"), _mode(UserMode()), _pass(false), _cap(true)
{}

/**
 * @brief Construct a new User:: User object
 */
User::User(void)
: _socketFd(-1), _username(""), _nickname(""), _realname(""), _hostname("irc"),
_servername("irc"), _mode(UserMode()), _pass(false), _cap(true)
{}

User::User(const User& ref)
: _socketFd(ref._socketFd), _username(ref._username), _nickname(ref._nickname), _realname(ref._realname), _hostname(ref._hostname),
_servername(ref._servername), _mode(ref._mode), _pass(ref._pass), _cap(ref._cap)
{}

/**
 * @brief Destroy the User:: User object
 */
User::~User(void) {}

// getter

/**
 * @brief Get the file descriptor of the client where the user is connected
 * 
 * @return int the file descriptor 
 */
int	User::getSocketFd(void) const {return _socketFd;}

/**
 * @brief Get the username of the user
 * 
 * @return std::string the username
 */
std::string	User::getUsername(void) const {return _username;}

/**
 * @brief Get the nickname of the user
 * 
 * @return std::string the nickname
 */
std::string	User::getNickname(void) const {return _nickname;}

/**
 * @brief Get the real name of the user
 * 
 * @return std::string the real name
 */
std::string	User::getRealname(void) const {return _realname;}

/**
 * @brief Get the hostname of the user
 * 
 * @return std::string the hostname
 */
std::string	User::getHostname(void) const {return _hostname;}

/**
 * @brief Get the servername of the user
 * 
 * @return std::string the servername
 */
std::string	User::getServername(void) const {return _servername;}

/**
 * @brief Get if the user send pass
 * 
 * @return bool the status
 */
bool	User::getPass(void) const {return _pass;}

/**
 * @brief Get if the user send caps
 * 
 * @return bool the status
 */
bool	User::getCap(void) const {return _cap;}

/**
 * @brief Get the mode status of invisible of the user
 * 
 * @return true if user mode invisible is on, else false
 */
bool	User::isInvisible(void) const {return _mode.getInvisible();}

/**
 * @brief Get the mode status of server notice of the user
 * 
 * @return true if user mode server notice is on, else false
 */
bool	User::isServerNotice(void) const {return _mode.getServerNotice();}

/**
 * @brief Get the mode status of Wall Operators of the user
 * 
 * @return true if user mode Wall Operators is on, else false
 */
bool	User::isWallOps(void) const {return _mode.getWallOps();}

/**
 * @brief Get the mode status of Operator Server of the user
 * 
 * @return true if user mode Operator Server is on, else false
 */
bool	User::isOperatorServer(void) const {return _mode.getOperatorServer();}


// setter

/**
 * @brief Set the file descriptor of the client where the user is connected
 * 
 * @param socketFd the file descriptor
 * @return User& the user
 */
User&	User::setSocketFd(const int socketFd) {_socketFd = socketFd;return *this;}

/**
 * @brief Set the username of the user
 * 
 * @param val the username
 * @return User& the user
 */
User&	User::setUsername(const std::string& val) {_username = val;return *this;}

/**
 * @brief Set the nickname of the user
 * 
 * @param val the nickname
 * @return User& the user
 */
User&	User::setNickname(const std::string& val) {_nickname = val;return *this;}

/**
 * @brief Set the real name of the user
 * 
 * @param val the real name
 * @return User& the user
 */
User&	User::setRealname(const std::string& val) {_realname = val;return *this;}

/**
 * @brief Set the hostname of the user
 * 
 * @param val the hostname
 * @return User& the user
 */
User&	User::setHostname(const std::string& val) {_hostname = val;return *this;}

/**
 * @brief Set the servername of the user
 * 
 * @param val the servername
 * @return User& the user
 */
User&	User::setServername(const std::string& val) {_servername = val;return *this;}

/**
 * @brief Set the pass of the user
 * 
 * @param val the pass status
 * @return User& the user
 */
User&	User::setPass(const bool val) {_pass = val;return *this;}

/**
 * @brief Set the caps of the user
 * 
 * @param val the pass status
 * @return User& the user
 */
User&	User::setCap(const bool val) {_cap = val;return *this;}

/**
 * @brief Set the mode status of invisible of the user
 * 
 * @param boolean true if user mode invisible is on, else false
 * @return User& the user
 */
User&	User::beInvisible(const bool boolean) {_mode.setInvisible(boolean);return *this;}

/**
 * @brief Set the mode status of server notice of the user
 * 
 * @param boolean true if user mode server notice is on, else false
 * @return User& the user
 */
User&	User::beServerNotice(const bool boolean) {_mode.setServerNotice(boolean);return *this;}

/**
 * @brief Set the mode status of Wall Operators of the user
 * 
 * @param boolean true if user mode Wall Operators is on, else false
 * @return User& the user
 */
User&	User::beWallOps(const bool boolean) {_mode.setWallOps(boolean);return *this;}

/**
 * @brief Set the mode status of Operator Server of the user
 * 
 * @param boolean true if user mode Operator Server is on, else false
 * @return User& the user
 */
User&	User::beOperatorServer(const bool boolean) {_mode.setOperatorServer(boolean);return *this;}


// utility

/**
 * @brief Send a command to a user
 * 
 * @param command the command that will be send
 * @return int 1 if the user is not connected, 2 if the send fail, else 0
 */
int	User::sendCommand(const std::string& command) const {
    Log log;
	if (_socketFd == -1) {
		std::cout << RED << log << "Send to user fail - no client" << NC << std::endl;
		return 1;
	}
	std::string	tmp = command + END;
	if (send(_socketFd, tmp.c_str(), tmp.size(), MSG_DONTWAIT) == -1) {
		std::cout << RED << "Send to user fail " << strerror(errno) << NC << std::endl;;
		return 2;
	}
	return 0;
}

/**
 * @brief check if user have requirements to register as user online
 * 
 * @param user the user
 * @return true if the user can be register, else false
 */
bool	User::isRegister() const {
	if (_nickname.size() && _username.size())
		return true;
	return false;
}
