#include "../includes/includes.hpp"

int main(int argc, char const *argv[])
{
	errno = 0;
	if (argc != 3) {
		std::cerr << "Error: usage: ./ircserv port password" << std::endl;
		return (EXIT_FAILURE);
	}
	try {
		irc::Server serv(argv[1], argv[2]);
		serv.connect();
	}
	catch(const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	
	return 0;
}
