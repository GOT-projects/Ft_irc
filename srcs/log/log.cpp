
#include "../../includes/includes.hpp"
#include <string>

using namespace irc;

Log::Log(){}

void Log::initLog(){
	_now = std::time(0);
	_ltm = std::localtime(&_now);
}

Log::~Log(){
}

std::tm *Log::getTm(){
	return (_ltm);
}

std::string Log::getTime(){
    std::string ret = std::to_string(1900 + _ltm->tm_year);
    ret.append("/");
    ret.append(std::to_string(1 + _ltm->tm_mon));
    ret.append("/");
    ret.append(std::to_string(_ltm->tm_mday));
    ret.append(" ");
    ret.append(std::to_string(_ltm->tm_hour));
    ret.append(":");
    ret.append(std::to_string(1 + _ltm->tm_min));
    ret.append(":");
    ret.append(std::to_string(1 + _ltm->tm_sec));
    return ret;
}

std::ostream & operator<< (std::ostream &o, Log &log) {
	log.initLog();
	std::tm *ltm = log.getTm();
	o << "[ " << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday << " " << ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1+  ltm->tm_sec << " ] ";
	return (o);
}

