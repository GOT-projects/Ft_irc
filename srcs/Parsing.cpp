#include "../includes/includes.hpp"

using namespace irc;

Parsing::Parsing (const int fd): _fd(fd){
    //Add msg to buffer for handl CTRL-D
    _completed = false;
}

Parsing::~Parsing(){
}

Parsing &Parsing::operator = (const Parsing &parsing){
    _fd = parsing._fd;
    _msg = parsing._msg;
    _buffer = parsing._buffer;
    _cmd = parsing._cmd;
    _cmds = parsing._cmds;
    _completed = parsing._completed;
	_readyTosend = false;
    return (*this);
}

Command::Command(std::string cmd, std::string prefix, std::vector<std::string> params)
: command(cmd), prefix(prefix), params(params){}

bool Parsing::getCompleted()const{
    return _completed;
}

std::vector<Command> Parsing::getCommand()const{
	return _cmds;
}

/**
 * @brief Clear Vector and reset bool to false
 * 
 */
void Parsing::ClearCommand(){
    _cmds.clear();
    _buffer.clear();
    _completed = false;
	_readyTosend = false;
}

/**
 * @brief Split msg receive and check if message finish by \r\n if not just append for waiting the end command
 * 
 * @param msg message
 * @param delimiter delimiter
 * @return std::vector<std::string> 
 */
std::vector<std::string>  Parsing::splitMsg(std::string &msg, const std::string &delimiter){
	std::vector<std::string>	result;
	std::string					str;
	size_t						end;

	_buffer.append(msg);
	if (!checkEndString(msg, "\r\n")){ 
		return result;
	}else{
		_completed = true;
	}
	str = _buffer;
	// first check 
	end = str.find(delimiter);
	if (end == std::string::npos)
		return (std::vector<std::string>());
	// save first command in vector
	if (end + delimiter.length() > MAX_CMD_LEN)
		throw std::runtime_error("Request too long");
	result.push_back(str.substr(0, end));

	// update str
	str.erase(0, end + delimiter.length());

	// loop for other commands
	end = str.find(delimiter);
	while (end != std::string::npos)
	{
		if (end + delimiter.length() > MAX_CMD_LEN)
			throw std::runtime_error("Request too long");
		result.push_back(str.substr(0, end));
		str.erase(0, end + delimiter.length());
		end = str.find(delimiter);
	}
	_buffer.clear();
	if (!str.empty())
		_buffer = str;
	return (result);
	}

	void Parsing::setReadyToSend(bool b){
	_readyTosend = b;
	}

	bool Parsing::getReadyToSend(void)const{
	return _readyTosend;
	}

	/**
	 * @brief Parse the command split for get CMD and the Params
	 * @param  cmd_splits
	 * @return  NONE
	 */
	void Parsing::splitCmds(std::vector<std::string> cmd_strings){
	std::vector<std::string>::iterator  it;
	size_t                              end;
	std::string                         prefix;

	if (_completed == false) {
		return;
	}
	_readyTosend = true;
	for (it = cmd_strings.begin(); it != cmd_strings.end(); ++it)
	{
		// extract CMD name
		end = it->find(' ');
		if (end == std::string::npos) // only the command
		{
			if (it->find(':') == 0){
				_completed = false;
				throw std::runtime_error("IRC itage must have a command");
			} // the only token is a prefix :'(
			_cmds.push_back(Command(it->substr(0, end)));
		}
		else // CMD + params
		{
			// CMD WITH PREFIX
			if (it->find(':') == 0)
			{
				prefix = it->substr(1, end);
				it->erase(0, end + 1);
				end = it->find(' ');
				if (end == std::string::npos)
				{
					_cmds.push_back(Command(*it, prefix));
					it->clear();
				}
				else
				{
					_cmds.push_back(Command(it->substr(0, end), \
										prefix));
					it->erase(0, end + 1);
				}
			}
			else // CMD WITH NO PREFIX
			{ 
				_cmds.push_back(Command(it->substr(0, end)));
				end = it->find(' ');
				if (end == std::string::npos)
					it->clear();
				else
					it->erase(0, end + 1);
			}
			// PARAMS
			if (!it->empty())
			{
				while (end != std::string::npos)
				{
					// if long param starting with ":"
					if (it->find(':') == 0)
					{
						_cmds.back().params.push_back(it->substr(1, \
															it->length() - 1));
						end = std::string::npos;
					}
					else
					{
						end = it->find(' ');
						if (end == std::string::npos)
							_cmds.back().params.push_back(*it);
						else
						{
							_cmds.back().params
								.push_back(it->substr(0, end));
							it->erase(0, end + 1);
						}
					}
				}
			}
		}
	}
	_buffer.clear();
	_completed = true;
	_tolowerCmd();
}

/**
 * @brief Iter Command for remove the /n
 * 
 */
void Parsing::_RemoveEmptyCmd(){
	std::vector<Command>::iterator  it;
	std::vector<std::string>::iterator  it2;
    int i(0);
	for (it = _cmds.begin(); it < _cmds.end(); ++it){
        trim_backspace(it->command);
		for (it2 = it->params.begin(); it2 < it->params.end(); ++it2){
            trim_backspace(it->params[i++]);
        }
    }
}

/**
 * @brief UPPERCASE the cmd
 * 
 */
void Parsing::_tolowerCmd(){
	std::vector<Command>::iterator  it;
    std::string::iterator itcmd;

	for (it = _cmds.begin(); it < _cmds.end(); ++it){
        transform((*it).command.begin(), (*it).command.end(), (*it).command.begin(), ::toupper);
    }
}

/**
 * @brief Print cmd receive use for DEBEUG
 * 
 */
void	Parsing::displayCommands() {

	std::vector<Command>::iterator  it;
	std::vector<std::string>::iterator  it2;
    int i(0);
	for (it = _cmds.begin(); it < _cmds.end(); ++it)
	{
		std::cout << "\nPREFIX : " << it->prefix << std::endl;
		std::cout << "CMD : " << it->command << std::endl;
		for (it2 = it->params.begin(); it2 < it->params.end(); ++it2)
		{
			std::cout << "\tPARAM " << i++ << ": " << *it2 << std::endl;
		}
	}
}

Command*	Parsing::getNextCmd() {
	if (_cmds.size() == 0)
		return NULL;
	return &(_cmds[0]);
}
