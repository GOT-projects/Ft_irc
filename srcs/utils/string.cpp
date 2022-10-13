#include "../../includes/includes.hpp"

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

std::string runUnixCommandAndCaptureOutput(std::string cmd) {
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

bool checkEndString(const std::string &msg, const std::string &regex){
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
