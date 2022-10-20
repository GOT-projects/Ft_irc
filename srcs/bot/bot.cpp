#include "../../includes/includes.hpp"
#include <cstdio>
#include <fstream>
#include <ostream>
#include <string>

using namespace irc;

Bot::Bot(){
	int i(0);
	std::string line;
	std::ifstream file;

	file.open ("./blacklist/blacklist.txt", std::ifstream::in);

	if (file.is_open())
	{
		while (!file.eof()){
			 std::getline(file, line);
			 line = line.substr(0, line.size() -1);
			_blacklist[line] = i++;
		}
		file.close();
	}else{
		std::cout << "Unable to open file"; 
	}
	std::cout << _blacklist.size() << std::endl;
	for (std::map<std::string, int>::iterator it = _blacklist.begin(); it != _blacklist.end(); ++it){
		std::cout << it->first << std::endl;
	}
}

Bot::~Bot(){
}

std::string Bot::blacklistMsg(std::string &msg)const{
	std::string ret;
	std::vector<std::string> split;

	 split = split_target(msg, ' ', false);
	 std::cout << "size of map " << _blacklist.size() << std::endl;
	 for (std::vector<std::string>::iterator it = split.begin(); it != split.end(); ++it){
		 std::cout << *it << "#" << std::endl;
		 if (_blacklist.find(*it) != _blacklist.end()){
			 std::cout << "blacklist found" << std::endl;
			 for (size_t i = 0; i < it->size(); ++i){
			 	ret.append("*");
			 }
		 }else{
			std::cout << *it << " blacklist not found" << std::endl;
			ret.append(*it);
		 }
		ret.append(" ");
	 }
	return ret;
}

