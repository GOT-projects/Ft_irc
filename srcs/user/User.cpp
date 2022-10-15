#include "../../includes/includes.hpp"

using namespace irc;

/**
 * @brief Construct a new User:: User object
 * 
 * @param fd file descriptor of client
 */
User::User(int fd)
: _socketFd(fd), _username(""), _nickname(""), _realname(""), _hostname(""),
_servername(""), _mode(UserMode())
{}

/**
 * @brief Construct a new User:: User object
 */
User::User(void)
: _socketFd(-1), _username(""), _nickname(""), _realname(""), _hostname(""),
_servername(""), _mode(UserMode())
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
 */
void	User::setSocketFd(const int socketFd) {_socketFd = socketFd;}

/**
 * @brief Set the username of the user
 * 
 * @param val the username
 */
void	User::setUsername(const std::string& val) {_username = val;}

/**
 * @brief Set the nickname of the user
 * 
 * @param val the nickname
 */
void	User::setNickname(const std::string& val) {_nickname = val;}

/**
 * @brief Set the real name of the user
 * 
 * @param val the real name
 */
void	User::setRealname(const std::string& val) {_realname = val;}

/**
 * @brief Set the hostname of the user
 * 
 * @param val the hostname
 */
void	User::setHostname(const std::string& val) {_hostname = val;}

/**
 * @brief Set the servername of the user
 * 
 * @param val the servername
 */
void	User::setServername(const std::string& val) {_servername = val;}

/**
 * @brief Set the mode status of invisible of the user
 * 
 * @param boolean true if user mode invisible is on, else false
 */
void	User::beInvisible(const bool boolean) {_mode.setInvisible(boolean);}

/**
 * @brief Set the mode status of server notice of the user
 * 
 * @param boolean true if user mode server notice is on, else false
 */
void	User::beServerNotice(const bool boolean) {_mode.setServerNotice(boolean);}

/**
 * @brief Set the mode status of Wall Operators of the user
 * 
 * @param boolean true if user mode Wall Operators is on, else false
 */
void	User::beWallOps(const bool boolean) {_mode.setWallOps(boolean);}

/**
 * @brief Set the mode status of Operator Server of the user
 * 
 * @param boolean true if user mode Operator Server is on, else false
 */
void	User::beOperatorServer(const bool boolean) {_mode.setOperatorServer(boolean);}


// utility

/**
 * @brief Send a command to a user
 * 
 * @param command the command that will be send
 * @return int 1 if the user is not connected, else 0
 */
int	User::sendCommand(const std::string& command) const {
	if (_socketFd == -1) {
		std::cout << RED << "Send to user fail - no client" << NC << std::endl;
		return 1;
	}
	// TODO if send fail
	send(_socketFd, command.c_str(), command.size(), O_NONBLOCK);
	return 0;
}
