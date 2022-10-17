#include "../../includes/includes.hpp"

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
	 * @brief Remove /n in string 
	 * 
	 * @param s the string to remove /n
	 * @return string with /n
	 */
    std::string trim_backspace(std::string &s){
        std::cout << "remove \\n" << std::endl;
        s.erase(s.find_last_not_of('\n')+1);         //suffixing spaces
        s.erase(0, s.find_first_not_of('\n'));       //prefixing spaces
        return s;
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


