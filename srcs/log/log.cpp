
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
	initLog();
	std::stringstream ss;
    ss <<  1900 + _ltm->tm_year;
    ss << '/';
    ss << 1 + _ltm->tm_mon;
    ss << "/";
    ss << _ltm->tm_mday;
    ss << " ";
    ss << _ltm->tm_hour;
    ss << ":";
    ss << 1 + _ltm->tm_min;
    ss << ":";
    ss << 1 + _ltm->tm_sec;
    return ss.str();
}

std::ostream & operator<< (std::ostream &o, Log &log) {
	log.initLog();
	std::tm *ltm = log.getTm();
	o << "[ " << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday << " " << ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1+  ltm->tm_sec << " ] ";
	return (o);
}

