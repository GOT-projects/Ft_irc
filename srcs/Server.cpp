#include "../includes/includes.hpp"
#include "../includes/runtime.hpp"

using namespace irc;

/**
 * @brief Construct a new Server:: Server object
 * 
 * @param port the number of the port
 * @param pwd the password of the server
 */
Server::Server(const std::string& port, const std::string& pwd, const std::string& operPassword)
: _operPassword(operPassword), _max_fd(0), _commands(Server::initCmd()), _bot()
{
	if (!is_number(port))
		throw std::out_of_range("port: not a number");
	int	tmp = atoi(port.c_str());
	if (tmp < 0 || tmp > 65535)
		throw std::out_of_range("port: out of range 0-65535");
	_port = static_cast<uint32_t>(tmp);
	_pwd = pwd;
	_portString = port;
	bzero(&_sockAddr, sizeof(_sockAddr));
	_sockServ = 0;
	std::cout << getLog() << GREEN << "Server created" << NC << std::endl;
}

Log& Server::getLog(){
	return _log;
}

/**
 * @brief return bot
 * 
 * @return bot
 */
Bot& Server::getBot(){
	return _bot;
}


/**
 * @brief Destroy the Server:: Server object
 * 
 */
Server::~Server(void) {
	for (int i = _sockServ + 1; i < _max_fd; i++)
	{
		if (FD_ISSET(i, &_currentSocket)) {
			killSocket(i);
		}
	}
	FD_CLR(_sockServ, &_currentSocket);
	close(_sockServ);
	std::cout << getLog() << GREEN << "Server shutdown" << NC << std::endl;
}

/**
 * @brief Create the socket and set all informations of the socket
 */
void	Server::createServer(void) {
	// Initialise information of the socket
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr = inet_addr(FT_INET_ADDR);
	_sockAddr.sin_port = htons(_port);
	// Create the socket
	if ((_sockServ = socket(AF_INET, SOCK_STREAM, FT_TCP_PROTOCOL)) < 0)
		throw std::runtime_error("error create socket server");
	int option = 1;
	if (setsockopt(_sockServ, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)) == -1)
		throw std::runtime_error(strerror(errno));
	/*if (setsockopt(_sockServ, IPPROTO_TCP, TCP_NODELAY, &option, sizeof(option)) == -1)
		throw std::runtime_error(strerror(errno));*/
	// Change socket control
	std::cout << getLog() << GREEN << "Server configured" << NC << std::endl;
}

/**
 * @brief Start the server, socket ready to recieve requests
 */
void	Server::runServer(void) const {
	Log log;
	if (
		// Change socket control
		fcntl(_sockServ, F_SETFL, O_NONBLOCK) == -1
		||
		// Link information of the socket with the socket
		bind(_sockServ, (struct sockaddr*)&_sockAddr, sizeof(_sockAddr)) == -1
		||
		// Start server (with SOCK_BACKLOG the max of demand waiting on socket)
		listen(_sockServ, FT_SOCK_BACKLOG) == -1
	)
		throw std::runtime_error(strerror(errno));
	std::cout << log << GREEN << "Server start" << NC << std::endl;
}

/**
 * @brief accept the connection of a new client
 * 
 * @param _max_fd the value of the fd open by the server which is higher
 */
void	Server::acceptNewConnection() {
	socklen_t	lenS = sizeof(_sockAddr);
	int newSocket = accept(_sockServ, (struct sockaddr*)&_sockAddr, &lenS);
	if (newSocket == -1)
		std::cerr << RED << "Accept: " << strerror(errno) << NC << std::endl;
	else
		std::cout << getLog() << "New client connection with socket " << newSocket << std::endl;
	// Creation of a new connection
	FD_SET(newSocket, &_currentSocket);
	_waitingUsers[newSocket] = User(newSocket);
	if (newSocket >= _max_fd)
		_max_fd = newSocket + 1;
	std::cout << getLog() << BLUE_BK << "Users" << NC << BLUE
		<< " In creation: " << _waitingUsers.size()
		<< " | online: " << _onlineUsers.size()
		<< NC << std::endl;
}

/**
 * @brief Destroy the connection - end of connection with the client (user)
 * 
 * @param fd file descriptor of the client
 */
void	Server::killSocket(const int fd) {
	FD_CLR(fd, &_currentSocket);
	shutdown(fd, SHUT_RDWR);
	close(fd);
	if (fd + 1 == _max_fd)
		_max_fd = fd;
	_Parse.erase(fd);
	std::cout << getLog() << RED << "Disconnected client with socket " << fd << NC << std::endl;
}

void Server::SendClient(int fd, const std::string &msg){
	send(fd, msg.c_str(), msg.length(), O_NONBLOCK);
}

/**
 * @brief Manage all clients interaction with the server, from post creation of
 * the connection to the end of connection
 * 
 * @param fd file descriptor of the client
 */
void	Server::handleClient(const int fd) {
	char    buff[1048];
	ssize_t ret;
	std::vector< std::string > cmd_string;

	bzero(buff, sizeof(buff));
	ret = recv(fd, &buff, sizeof(buff), MSG_DONTWAIT);
	if (ret <= 0){
		killClient(*getUser(fd));
	} else {
		// server receive
		std::string tmp = buff;
		if (_Parse.find(fd) == _Parse.end())
			_Parse[fd] = Parsing(fd);
		try{
			cmd_string = _Parse[fd].splitMsg(tmp, "\r\n");
		}
		catch (std::runtime_error &e) { 
			SendClient(fd, "ERROR : :" + std::string(e.what()) + "\r\n");
			killSocket(fd);
			return;
		}
		try {
			_Parse[fd].splitCmds(cmd_string);
		}catch (std::runtime_error &e) { 
			SendClient(fd, "ERROR : :" + std::string(e.what()) + "\r\n");
		}
		//_Parse[fd].displayCommands();
		if (_Parse[fd].getCompleted()){
			//std::cout << getLog() << tmp << YELLOW_BK << "END OF RECEPTION" << NC << std::endl;
			//std::cout << getLog() << YELLOW << "Client with the socket " << fd << " receive :" << NC << std::endl;
			this->ExecuteCmd(fd);
		}
	}
}


/* @Brief Execute cmd of irc server from cmd reveceive*/
/* @Param  int fd*/
/* @Return  NONE*/
void Server::ExecuteCmd(int fd){
	User*	user = getUser(fd);
	if (_Parse[fd].getNextCmd() == NULL) {
		std::cerr << getLog() << RED << "NO COMMAND" << NC << std::endl;
		return ;
	}
	mapCommandConstIterator 		cmd      = _commands.begin();
	std::vector<Command>			cmds     = _Parse[fd].getCommand();
	std::vector<Command>::iterator	itcmd    = cmds.begin();
	std::vector<Command>::iterator	itcmdEnd = cmds.end();
	functionPtr executeCmd;

	for (; itcmd != itcmdEnd; itcmd++){
		if (_commands.find((*itcmd).command) != _commands.end()){
			std::cerr << getLog() <<GREEN << "COMMAND " << (*itcmd).command << " FOUND" << NC << std::endl;
			cmd = _commands.find(itcmd->command);
			executeCmd = cmd->second;
			if (canExecute(*this, *user, itcmd->command))
				executeCmd(*this, *user, *itcmd);
		}else{
			std::cerr << getLog() << RED << "COMMAND " << (*itcmd).command << " NOT FOUND"<< NC << std::endl;
			user->sendCommand(ERR_UNKNOWNCOMMAND((*itcmd).command));
		}
	}
	_Parse[fd].ClearCommand();
}

/**
 * @brief Create and open the port of the server
 * 
 * Connection between the server and the clients
 */
void	Server::connect(void) {
	fd_set	readySocket;

	createServer();
	runServer();
	display();
	_max_fd = _sockServ + 1;
	FD_ZERO(&_currentSocket);
	FD_SET(_sockServ, &_currentSocket);
	runtimeServer = 1;
	while (runtimeServer)
	{
		readySocket = _currentSocket;
		if (select(_max_fd + 1, &readySocket, NULL, NULL, NULL) < 0)
			throw std::runtime_error(strerror(errno));
		for (int fd = 0; fd <= _max_fd; fd++) {
			if (FD_ISSET(fd, &readySocket)) {
				if (fd == _sockServ) {
					acceptNewConnection();
				}
				else {
					handleClient(fd);
				}
			}
		}
	}
}

/**
 * @brief Display at the start of the server
 */
void Server::display(void){
	std::string ipLan = runUnixCommandAndCaptureOutput("ifconfig  | grep -e 'inet .*broadcast ' | awk '{ print $2 }' | head -n1");
	std::cout << "┌───────────────────────────────────────────────┐" << std::endl;
	std::cout << "│                                               │" << std::endl;
	std::cout << "│ " << std::setw(25) << std::right << "ft_irc v1" << std::setw(24) << "│" << std::endl;
	std::cout << "│ " << std::setw(14) << std::right << "(host " << ipLan << " " << "port: " << _portString << ")" << std::setw(27 - _portString.length() - ipLan.length()) <<  "│" << std::endl;
	std::cout << "│                                               │" << std::endl;
	std::cout << "│ " << "Bind " << std::setfill('.') << std::setw(10)<< _sockServ << std::setfill(' ') 
				  << std::setw(20) << std::right << "Processes " << std::setfill('.') << std::setw(10)<< '1' << std::setfill(' ') << " │" << std::endl;
	std::cout << "│ " << "Pid " << std::setfill('.') << std::setw(14)<< getpid() << std::setfill(' ') << std::setw(31) << " │" << std::endl;
	std::cout << "│                                               │" << std::endl;
	std::cout << "└───────────────────────────────────────────────┘" << std::endl;
}

/**
 * @brief Get the online users
 * 
 * @return listUser& list of online users
 */
listUser&	Server::getOnlineUsers( void ){
	return (this->_onlineUsers);
}



/**
 * @brief Get the waiting users (not register users)
 * 
 * @return mapUser& map of waiting users (not register users)
 */
mapUser&	Server::getWaitingUsers( void ){
	return (this->_waitingUsers);
}

/**
 * @brief Research and get a user in all users of the server
 * 
 * @param fd file descriptor of the client
 * @return User* NULL if not find, else pointer on user
 */
User*	Server::getUser(int fd) {
	if (_waitingUsers.find(fd) != _waitingUsers.end())
		return &(_waitingUsers[fd]);
	User*	online = getUserInList(User(fd), _onlineUsers, &isSameSocket);
	return (online);
}

/**
 * @brief Get the password of the server
 * 
 * @return std::string the server password
 */
std::string	Server::getPassword() const {
	return _pwd;
}

/**
 * @brief chope la mapChannel
 * 
 * @return mapChannel& 
 */
mapChannel&	Server::getMapChannel( void ){
	return (this->_channels);
}

/**
 * @brief check la presence du chan
 * 
 * @return true or false
 */
bool	Server::isInMapChannel(std::string chan) {
	if (this->getMapChannel().size() == 0)
		return (false);
	if (this->getMapChannel().find(chan) != this->getMapChannel().end())
		return (true);
	return (false);
}

/**
 * @brief kill a user from server
 * 
 * @param user the user
 */
void	Server::killClient(User& user) {
	killSocket(user.getSocketFd());
	int err = 1;
	// remove from channels
	{
		mapChannelIterator it = getMapChannel().begin();
		while (it != getMapChannel().end())
		{
			if (it->second.kick(user) == 2) {
				mapChannelIterator	tmp = it;
				it++;
				getMapChannel().erase(tmp);
				std::cout << _log << BLUE_BK << "Channels" << NC << BLUE << " Open: " << _channels.size() << NC << std::endl;

			} else
				it++;
		}
	}
	{ // remove from server
		mapUserIterator		itWaiting = getUserIteratorInMap(user, getWaitingUsers(), &isSameSocket);
		if (itWaiting != getWaitingUsers().end()) {
			getWaitingUsers().erase(itWaiting);
			err = 0;
		} else { 
			listUserIterator	itOnline = getUserIteratorInList(user, getOnlineUsers(), &isSameSocket);
			if (itOnline != getOnlineUsers().end()) {
				getOnlineUsers().erase(itOnline);
				err = 0;
			}
		}
	}
	if (err)
		std::cerr << getLog() << RED_ERR << "killClient" << RED << ": Error fatal - user not found" << NC << std::endl;
	else {
		std::cout << getLog() << BLUE_BK << "Users" << NC << BLUE
			<< " In creation: " << _waitingUsers.size()
			<< " | online: " << _onlineUsers.size()
			<< NC << std::endl;
	}
}

/**
 * @brief get the password to become operator
 * 
 * @return std::string the password
 */
std::string	Server::getOperPassword() const {
	return _operPassword;
}
