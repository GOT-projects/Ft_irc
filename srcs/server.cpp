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
		fd_set	read;
		fd_set	write;
		FD_ZERO(&read);
		FD_ZERO(&write);
		FD_SET(_sockServ, &read);
	while (true)
	{
		std::cout << (_clients.empty() ? _sockServ : (_clients.end())->first) + 1 << std::endl;
		int activity = select(, &read, NULL, NULL, NULL);
		std::cout << activity << std::endl;
		std::cout << "foo" << std::endl;
		if (activity < 0)
			throw std::runtime_error(strerror(errno));
		int client = accept(_sockServ, NULL, NULL);
		if (client >= 0) {
			if (DEBUG)
				std::cout << "Connection new client" << std::endl;
			_clients.insert(pair_type(client, client));
			for (map_iterator it = _clients.begin(); it != _clients.end(); it++)
				std::cout << it->first << " " << it->second << std::endl;
			std::cout << std::endl;
		}
	}
}
