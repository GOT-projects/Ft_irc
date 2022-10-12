/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aartiges jmilhas rcuminal <x@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:16:05 by jmilhas           #+#    #+#             */
/*   Updated: 2022/10/12 22:37:25 by aartiges jm      ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
