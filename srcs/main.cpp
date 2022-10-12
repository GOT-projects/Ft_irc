#include "../includes/includes.hpp"

int main(int argc, char const *argv[])
{
	errno = 0;
	if (argc != 3) {
		std::cerr << RED << "Error: usage: ./ircserv port password" << NC << std::endl;
		return (EXIT_FAILURE);
	}
	try {
		irc::Server serv(argv[1], argv[2]);
		serv.connect();
	}
	catch(const std::exception& e) {
		std::cerr << RED_ERR << "Exception: " << RED << e.what() << NC << std::endl;
	}
	
	return 0;
}
