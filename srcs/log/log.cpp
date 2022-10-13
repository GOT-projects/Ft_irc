
#include "../../includes/includes.hpp"

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

std::ostream & operator<< (std::ostream &o, Log &log) {
    log.initLog();
    std::tm *ltm = log.getTm();
	o << "[ " << 1900 + ltm->tm_year << "/" << 1 + ltm->tm_mon << "/" << ltm->tm_mday << " " << 5 + ltm->tm_hour << ":" << 30 + ltm->tm_min << ":" << ltm->tm_sec << " ] ";
	return (o);
}

