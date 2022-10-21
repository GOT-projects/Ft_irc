#include "../../includes/includes.hpp"
#include <algorithm>
#include <string>

namespace irc
{
	/**
	 * @brief Check if a string is a number (contain only digits)
	 * 
	 * @param s the string to test
	 * @return true if s is a number, else false
	 */
	bool	is_number(const std::string& s)
	{
		std::string::const_iterator it = s.begin();
		while (it != s.end() && std::isdigit(*it)) ++it;
		return !s.empty() && it == s.end();
	}

	/**
	 * @brief split the string with ',' for get all target client
	 * 
	 * @param s string to slipt
	 * @return vector of target	 
     */
    std::vector<std::string>split_target(const std::string &s, char sep, bool lower){
        std::vector<std::string> ret;
        std::string tmp;
        std::istringstream stream(s);
        if (s.find(sep) == std::string::npos){
            ret.push_back(s);
            return ret;
        }
        while (std::getline(stream, tmp, sep)){
			if (lower)
            	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            ret.push_back(tmp);
        }
        return ret;
    }


	/**
	 * @brief Remove /n in string 
	 * 
	 * @param s the string to remove /n
	 * @return string with /n
	 */
    std::string trim_backspace(std::string &s){
        std::string ret;
        std::string::difference_type n = std::count(s.begin(), s.end(), '\n');
        if (n == 1)
            return s;
        for (std::string::iterator it = s.begin(); it != s.end(); ++it){
            if (*it == '\r' && *it + 1 == '\n'){
                ret.append("\r\n");
                it+2;
            }else if (*it != '\n' && it != s.end() - 1){
                ret.append(&(*it));
            }
        }
        return ret;
    }

	/**
	 * @brief Run a command and capture output in a string
	 * 
	 * @param cmd the unix command to run
	 * @return std::string the output of the command
	 */
	std::string	runUnixCommandAndCaptureOutput(std::string cmd) {
		char buffer[128];
		std::string result = "";
		FILE* pipe = popen(cmd.c_str(), "r");
		if (!pipe) throw std::runtime_error("popen() failed!");
		try {
			while (!feof(pipe)) {
			if (fgets(buffer, 128, pipe) != NULL)
				result += buffer;
			}
		} catch (...) {
			pclose(pipe);
			throw;
		}
		pclose(pipe);
		return result.substr(0, result.length() -1);
	}

	/**
	 * @brief Check if the end of a string match with the regex
	 * 
	 * @param msg the string to check
	 * @param regex the regex to test
	 * @return true if the string match with the regex, else false
	 */
	bool	checkEndString(const std::string &msg, const std::string &regex){
		std::string::const_reverse_iterator itMsg = msg.rbegin();
		std::string::const_reverse_iterator itRegex = regex.rbegin();

		if (msg.length() < regex.length())
			return false;

		for (; itRegex != regex.rend(); itRegex++, itMsg++){
			if (*itMsg != *itRegex)
				return false;
		}
		return true;
	}
} // namespace irc


