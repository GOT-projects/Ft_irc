#include "../../includes/includes.hpp"

using namespace irc;

/**
 * @brief Construct a new User Mode:: User Mode object
 */
UserMode::UserMode(void) : _invisible(false), _serverNotice(false), _wallOps(false), _operatorServer(false) {}

UserMode::UserMode(const UserMode& ref)
: _invisible(ref._invisible), _serverNotice(ref._serverNotice), _wallOps(ref._wallOps), _operatorServer(ref._operatorServer) {}

/**
 * @brief Destroy the User Mode:: User Mode object
 */
UserMode::~UserMode(void) {}


/**
 * @brief Get the mode status of invisible of the user
 * 
 * @return true if user mode invisible is on, else false
 */
bool	UserMode::getInvisible(void) const {
	return _invisible;
}

/**
 * @brief Get the mode status of server notice of the user
 * 
 * @return true if user mode server notice is on, else false
 */
bool	UserMode::getServerNotice(void) const {
	return _serverNotice;
}

/**
 * @brief Get the mode status of Wall Operators of the user
 * 
 * @return true if user mode Wall Operators is on, else false
 */
bool	UserMode::getWallOps(void) const {
	return _wallOps;
}

/**
 * @brief Get the mode status of Operator Server of the user
 * 
 * @return true if user mode Operator Server is on, else false
 */
bool	UserMode::getOperatorServer(void) const {
	return _operatorServer;
}

/**
 * @brief Set the mode status of invisible of the user
 * 
 * @param boolean true if user mode invisible is on, else false
 */
void	UserMode::setInvisible(const bool boolean) {
	_invisible = boolean;
}

/**
 * @brief Set the mode status of server notice of the user
 * 
 * @param boolean true if user mode server notice is on, else false
 */
void	UserMode::setServerNotice(const bool boolean) {
	_serverNotice = boolean;
}

/**
 * @brief Set the mode status of Wall Operators of the user
 * 
 * @param boolean true if user mode Wall Operators is on, else false
 */
void	UserMode::setWallOps(const bool boolean) {
	_wallOps = boolean;
}

/**
 * @brief Set the mode status of Operator Server of the user
 * 
 * @param boolean true if user mode Operator Server is on, else false
 */
void	UserMode::setOperatorServer(const bool boolean) {
	_operatorServer = boolean;
}
