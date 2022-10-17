#include "../includes/includes.hpp"

/**
 * @brief The main program (entry)
 * 
 * @param argc number og arguments
 * @param argv arguments pass
 * @return int 0 if success, else failure
 */
int main(int argc, char const *argv[])
{
    irc::Log log;
	errno = 0;
	if (argc != 3) {
		std::cerr << log << RED << "Error: usage: ./ircserv port password" << NC << std::endl;
		return (EXIT_FAILURE);
	}
	try {
		irc::Server serv(argv[1], argv[2]);
		serv.connect();
	}
	catch(const std::exception& e) {
		std::cerr << log << RED_ERR << "Exception: " << NC << RED << e.what() << NC << std::endl;
	}
	
	return 0;
}
