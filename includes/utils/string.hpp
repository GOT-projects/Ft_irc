#pragma once

#include "../includes.hpp"

namespace irc
{
	/**
	 * @brief All functions here, are for string check and manipulations
	 */


	bool						is_number(const std::string& s);
	std::string					runUnixCommandAndCaptureOutput(std::string cmd);
	bool						checkEndString(const std::string &msg, const std::string &regex);
	std::string					trim_backspace(std::string &params);
	std::vector<std::string>	split_target(const std::string &s, char sep, bool lower);

} // namespace irc
