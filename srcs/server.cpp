#include "../includes/server.hpp"

using namespace irc;

/**
 * @brief Construct a new Server:: Server object
 * 
 * @param port the number of the port
 * @param pwd the password of the server
 */
Server::Server(const std::string& port, const std::string& pwd)
{
	int	tmp = std::stoi(port.c_str());
	if (tmp < 0 || tmp > 65535)
		throw std::out_of_range("port: out of range 0-65535");
	_port = static_cast<uint32_t>(tmp);
	_pwd = pwd; // TODO politic
	bzero(&_sockAddr, sizeof(_sockAddr));
	_sockServ = 0;
	std::cout << GREEN << "Server created" << NC << std::endl;
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
	// TODO F_SETFL
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
	if (newSocket >= max_fd)
		max_fd = newSocket + 1;
}

void	Server::killSocket(fd_set& currentSocket, const int fd, int& max_fd) {
	FD_CLR(fd, &currentSocket);
	close(fd);
	if (fd + 1 == max_fd)
		max_fd = fd;
	std::cout << RED << "Disconnected client with socket " << fd << NC << std::endl;
}

void	Server::handleClient(fd_set& currentSocket, const int fd, int& max_fd) {
	// TODO all
	char buff[5000];
	bzero(buff, sizeof(buff));
	if (recv(fd, &buff, sizeof(buff), O_NONBLOCK) <= 0) {
		killSocket(currentSocket, fd, max_fd);
	} else {
		// server receive
		std::string tmp = buff;
		//std::replace( tmp.begin(), tmp.end(), '\r', '#');
		//std::replace( tmp.begin(), tmp.end() - 1, '\n', '_');
		std::cout << "fd " << fd << " receive: " << tmp;
		std::cout << YELLOW << "Client with the socket " << fd << " receive :" << NC << std::endl;
		std::cout << tmp << YELLOW_BK << "END OF RECEPTION" << NC << std::endl;
		send(fd, ":127.0.0.1 001 aartiges :Welcome aartiges!aartiges@127.0.0.1\r\n", 63, O_NONBLOCK);
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
	struct timeval	tv;
	int max_fd;

	createServer();
	runServer();
	tv.tv_sec = 1;
	tv.tv_usec = 1000;
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


