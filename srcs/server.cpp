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
}

/**
 * @brief Destroy the Server:: Server object
 * 
 */
Server::~Server() {}

/**
 * @brief Create and open the port of the server
 * 
 * Connection between the server and the clients
 * 
 */
void	Server::connect() {
	// Create socket
	_sockServ = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockServ < 0)
		throw std::runtime_error("error create socket server");
	if (fcntl(_sockServ, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error(strerror(errno));
	if (DEBUG)
		std::cout << "Socket created" << std::endl;
	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_sockAddr.sin_port = htons(_port);


	// Run server
	if (bind(_sockServ, (struct sockaddr*)&_sockAddr, sizeof(_sockAddr)) == -1
		|| listen(_sockServ, 100) == -1)
		throw std::runtime_error(strerror(errno));
	if (DEBUG)
		std::cout << "Server open on port " << _port << std::endl;

	struct timeval	tv;
	tv.tv_sec = 1;
	tv.tv_usec = 1000;
	int max_fd = _sockServ + 1;
	fd_set	currentSocket, readySocket;
	FD_ZERO(&currentSocket);
	FD_SET(_sockServ, &currentSocket);
	while (true)
	{
		readySocket = currentSocket;
		if (select(max_fd + 1, &readySocket, NULL, NULL, NULL) < 0)
			throw std::runtime_error(strerror(errno));
		for (int i = 0; i <= max_fd; i++) {
			if (FD_ISSET(i, &readySocket)) {
				if (i == _sockServ) {
					// new
					socklen_t	lenS;
					int newSocket = accept(_sockServ, (struct sockaddr*)&_sockAddr, &lenS);
					if (newSocket >= 0) {
						if (DEBUG)
							std::cout << "fd: " << newSocket << " Connection new client" << std::endl;
					}
					else
						throw std::runtime_error(strerror(errno)); // TODO rm
					FD_SET(newSocket, &currentSocket);
					if (newSocket >= max_fd)
						max_fd = newSocket + 1;
				}
				else {
					// TODO taff
					char buff[5000];
					bzero(buff, sizeof(buff));
					if ((recv(i, &buff, sizeof(buff), O_NONBLOCK)) <= 0 || strcmp(buff, "quit\n") == 0) {
						FD_CLR(i, &currentSocket);
						close(i);
						std::cout << RED << "fd " << i << " gone" << NC << std::endl;
					} else {
						// server receive
						std::string tmp = buff;
						//std::replace( tmp.begin(), tmp.end(), '\r', '#');
						//std::replace( tmp.begin(), tmp.end() - 1, '\n', '_');
				    	std::cout << "fd " << i << " receive: " << tmp;
				    	send(i, ":127.0.0.1 001 aartiges :Welcome aartiges!aartiges@127.0.0.1\r\n", 63, O_NONBLOCK);

					}
					// send command for client
				}
			}
		}
	}
}


