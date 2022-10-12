#include "../../includes/includes.hpp"

using namespace irc;

/**
 * @brief Construct a new User Mode:: User Mode object
 * 
 */
UserMode::UserMode(void) : _invisible(false), _serverNotice(false), _wallOps(false), _operatorServer(false) {}

/**
 * @brief Destroy the User Mode:: User Mode object
 * 
 */
UserMode::~UserMode(void) {}


bool	UserMode::getInvisible(void) const {
	return _invisible;
}
bool	UserMode::getServerNotice(void) const {
	return _serverNotice;
}
bool	UserMode::getWallOps(void) const {
	return _wallOps;
}
bool	UserMode::getOperatorServer(void) const {
	return _operatorServer;
}
void	UserMode::setInvisible(const bool boolean) {
	_invisible = boolean;
}
void	UserMode::setServerNotice(const bool boolean) {
	_serverNotice = boolean;
}
void	UserMode::setWallOps(const bool boolean) {
	_wallOps = boolean;
}
void	UserMode::setOperatorServer(const bool boolean) {
	_operatorServer = boolean;
}
