#include "../includes/includes.hpp"
#include <iostream>

#define test ":ft_irc 433 aartiges :Nickname is already in user\r\n"

using namespace irc;

/**
 * @brief Construct a new Server:: Server object
 * 
 * @param port the number of the port
 * @param pwd the password of the server
 */
Server::Server(const std::string& port, const std::string& pwd) : _commands(Server::initCmd())
{
	if (!is_number(port))
		throw std::out_of_range("port: not a number");
	int	tmp = atoi(port.c_str());
	if (tmp < 0 || tmp > 65535)
		throw std::out_of_range("port: out of range 0-65535");
	_port = static_cast<uint32_t>(tmp);
	_pwd = pwd; // TODO politic
	_portString = port;
	bzero(&_sockAddr, sizeof(_sockAddr));
	_sockServ = 0;
    _log = Log();
	std::cout << GREEN << "Server created" << NC << std::endl;
}

Log Server::getLog(){
    return _log;
}


/**
 * @brief Destroy the Server:: Server object
 * 
 */
Server::~Server(void) {
	std::cout << GREEN << "Server shutdown" << NC << std::endl;
}

/**
 * @brief Create the socket and set all informations of the socket
 * 
 */
void	Server::createServer(void) {
	// Initialise information of the socket
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr = inet_addr(FT_INET_ADDR);
	_sockAddr.sin_port = htons(_port);
	// Create the socket
	if ((_sockServ = socket(AF_INET, SOCK_STREAM, FT_TCP_PROTOCOL)) < 0)
		throw std::runtime_error("error create socket server");
	// Change socket control
	std::cout << GREEN << "Server configured" << NC << std::endl;
}

/**
 * @brief Start the server, socket ready to recieve requests
 * 
 */
void	Server::runServer(void) const {
	if (
		// Change socket control
		fcntl(_sockServ, F_SETFL, O_NONBLOCK) == -1
		// TODO F_SETFL
		||
		// Link information of the socket with the socket
		bind(_sockServ, (struct sockaddr*)&_sockAddr, sizeof(_sockAddr)) == -1
		||
		// Start server (with SOCK_BACKLOG the max of demand waiting on socket)
		listen(_sockServ, FT_SOCK_BACKLOG) == -1
	)
		throw std::runtime_error(strerror(errno));
	std::cout << GREEN << "Server start" << NC << std::endl;
}

/**
 * @brief accept the connection of a new client
 * 
 * @param currentSocket list of all socket (fd) already open by to communicate
 * with the clients
 * @param max_fd the value of the fd open by the server which is higher
 */
void	Server::acceptNewConnection(fd_set&	currentSocket, int& max_fd) {
	socklen_t	lenS;
	int newSocket = accept(_sockServ, (struct sockaddr*)&_sockAddr, &lenS);
	std::cout << "New client connection with socket " << newSocket << std::endl;
	// TODO add creation of a new connection
	FD_SET(newSocket, &currentSocket);
	_waitingUsers[newSocket] = User(newSocket);
	if (newSocket >= max_fd)
		max_fd = newSocket + 1;
}

void	Server::killSocket(fd_set& currentSocket, const int fd, int& max_fd) {
	FD_CLR(fd, &currentSocket);
	close(fd);
	// RM user if user not create
	if (_waitingUsers.find(fd) != _waitingUsers.end())
		_waitingUsers.erase(fd);
	else { // Disconnect user
		listUserIterator	tmp = disconnectUserIn(fd, _onlineUsers);
		if (tmp != _onlineUsers.end()) {
			_offlineUsers.push_back(*tmp);
			_onlineUsers.erase(tmp);
		}
	}
	if (fd + 1 == max_fd)
		max_fd = fd;
	//TODO rm user - rm parse
	_Parse.erase(fd);
	std::cout << RED << "Disconnected client with socket " << fd << NC << std::endl;
}

void Server::SendClient(int fd, const std::string &msg){
	send(fd, msg.c_str(), msg.length(), O_NONBLOCK);
}

void	Server::handleClient(fd_set& currentSocket, const int fd, int& max_fd) {
	// TODO Need working on CTRl-D
	char    buff[1048];
	ssize_t ret;
	std::vector< std::string > cmd_string;

	bzero(buff, sizeof(buff));
	ret = recv(fd, &buff, sizeof(buff), O_NONBLOCK);
	if (ret <= 0){
		killSocket(currentSocket, fd, max_fd);
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
			killSocket(currentSocket, fd, max_fd);
			return;
		}
		try {
			_Parse[fd].splitCmds(cmd_string);
		}catch (std::runtime_error &e) { 
			SendClient(fd, "ERROR : :" + std::string(e.what()) + "\r\n");
		}
		std::cout << _log;
		_Parse[fd].displayCommands();
		// TODO ctl+v nc \r  /!\ not rm comment
		// TODO run multiple cmd
		if (_Parse[fd].getCompleted()){
			//std::cout << _log << "fd " << fd << " receive: " << tmp;
			std::cout << YELLOW << "Client with the socket " << fd << " receive :" << NC << std::endl;
			std::cout << tmp << YELLOW_BK << "END OF RECEPTION" << NC << std::endl;
			User*	user = getUser(fd);
			if (_Parse[fd].getNextCmd() == NULL) {
				std::cerr << RED << "NO COMMAND" << NC << std::endl;
				return ;
			}
			std::cout << "wep" << std::endl;
            mapCommandConstIterator cmd = _commands.begin();
            std::vector<Command> cmds = _Parse[fd].getCommand();
            std::vector<Command>::iterator itcmd = cmds.begin();
            std::vector<Command>::iterator itcmdEnd= cmds.end();
            functionPtr executeCmd;

            for (; itcmd != itcmdEnd; itcmd++){
                if (_commands.find((*itcmd).command) != _commands.end()){
				    std::cerr <<GREEN << "COMMAND " << (*itcmd).command << " FOUND" << NC << std::endl;
                    cmd = _commands.find(itcmd->command);
                    executeCmd = cmd->second;
                    executeCmd(*this, *user, *itcmd);
                }else{
                    std::cerr << RED << "COMMAND " << (*itcmd).command << " NOT FOUND"<< NC << std::endl;
                }
            }
            _Parse[fd].getCommand().erase(itcmd, cmds.end());

			/* 	//TODO send error user.sendCommand(...) */
			/* 	std::cerr << RED << "COMMAND NOT FOUND" << NC << std::endl; */
			/* _Parse[fd].rmFirstCmd(); */
			//_Parse[fd].setReadyToSend(false);
	}
	// TODO if (_waitingUsers.find(fd) != _waitingUsers.end() && user finish && !exist)
	// online <- user
	// rm user
	// TODO if (_waitingUsers.find(fd) != _waitingUsers.end() && user finish && exist)
	// rm user
	// online fd = fd
    }
}

/**
 * @brief Create and open the port of the server
 * 
 * Connection between the server and the clients
 * 
 */
void	Server::connect(void) {
	fd_set	currentSocket, readySocket;
	int max_fd;

	createServer();
	runServer();
	display();
	max_fd = _sockServ + 1;
	FD_ZERO(&currentSocket);
	FD_SET(_sockServ, &currentSocket);

	while (true)
	{
		readySocket = currentSocket;
		if (select(max_fd + 1, &readySocket, NULL, NULL, NULL) < 0)
			throw std::runtime_error(strerror(errno));
		for (int fd = 0; fd <= max_fd; fd++) {
			if (FD_ISSET(fd, &readySocket)) {
				std::cout << BLUE_BK << "Users" << NC << BLUE
					<< " In creation: " << _waitingUsers.size()
					<< " online: " << _onlineUsers.size()
					<< " offline: " << _offlineUsers.size()
					<< NC << std::endl;

				if (fd == _sockServ) {
					acceptNewConnection(currentSocket, max_fd);
				}
				else {
					handleClient(currentSocket, fd, max_fd);
				}
			}
		}
	}
}


void Server::display(void){
	std::string ipLan = runUnixCommandAndCaptureOutput("ifconfig  | grep -e 'inet .*broadcast ' | awk '{ print $2 }'");
	std::cout << "┌───────────────────────────────────────────────┐" << std::endl;
	std::cout << "│                                               │" << std::endl;
	std::cout << "│ " << std::setw(25) << std::right << "ft_irc v1" << std::setw(24) << "│" << std::endl;
	std::cout << "│ " << std::setw(14) << std::right << "(host " << ipLan << " " << "port: " << _portString << ")" << std::setw(27 - _portString.length() - ipLan.length()) <<  "│" << std::endl;
	std::cout << "│                                               │" << std::endl;
	std::cout << "│ " << "Bind " << std::setfill('.') << std::setw(10)<< _sockServ << std::setfill(' ') 
		          << std::setw(20) << std::right << "Processes " << std::setfill('.') << std::setw(10)<< '1' << std::setfill(' ') << " │" << std::endl;
	std::cout << "│ " << "Pid " << std::setfill('.') << std::setw(15)<< getpid() << std::setfill(' ') << std::setw(30) << " │" << std::endl;
	std::cout << "│                                               │" << std::endl;
	std::cout << "└───────────────────────────────────────────────┘" << std::endl;
}

listUser&	Server::getOnlineUsers( void ){
	return (this->_onlineUsers);
}

listUser&	Server::getOfflineUsers( void ){
	return (this->_offlineUsers);
}

mapUser&	Server::getWaitingUsers( void ){
	return (this->_waitingUsers);
}

User*	Server::getUser(int fd) {
	if (_waitingUsers.find(fd) != _waitingUsers.end())
		return &(_waitingUsers[fd]);
	User*	online = getUserInList(fd, _onlineUsers);
	User*	offline = getUserInList(fd, _offlineUsers);
	return (online == NULL ? offline : online);
}
