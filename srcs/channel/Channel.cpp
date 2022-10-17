#include "../../includes/includes.hpp"
#include <iostream>

using namespace irc;

/**
 * @brief Change the channel password
 * 
 * @param pass new password
 */
void	Channel::changeChanPassword( std::string pass ){
	_password = pass;
}

/**
 * @brief Change the channel topic
 * 
 * @param name new topic
 */
void	Channel::changeChanTopic( std::string name ){
	_topic = name;
}

/**
 * @brief Change the channel name
 * 
 * @param name new name
 */
void	Channel::changeChanName( std::string name ){
	_channelName = name;
}

/**
 * @brief Permit to add operator mode (in channel) at guest
 * if host has the good rights.
 * 
 * If host hasn't permissions, do nothing
 * 
 * @param host the user that give the operator mode
 * @param guest the user that receive the operator mode
 */
void	Channel::giveRights( User& host, User& guest){
	if (this->isInOperatorList(host.getNickname()) && !this->isInBanList(guest.getNickname()))
		this->addToOperatorList(guest);
}

/**
 * @brief Check if the password is the channel password
 * 
 * @param str the password to check
 * @return true passwords match
 * @return false passwords dismatch
 */
bool	Channel::checkPassword( std::string str){
	if (str == this->_password)
		return (true);
	return (false);
}

// void    Channel::inviteToChannel(){  // args: invité, invitant
// 	//if invitant peut inviter et mode le permet
// 		//if invité peut etre invite (pas blacklister)
// 			//ft_join
// }


/**
 * @brief Send message to all users of the channel
 * 
 * @param message message to send
 */
void	Channel::sendMessage( std::string message ){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++)
		(*it)->sendCommand(message.c_str());
}

/**
 * @brief Send message to all users of the channel, original thrower expected
 * 
 * @param message message to send
 */
void	Channel::sendMessage( std::string message , User& user){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++){
		if ((*it)->getNickname() != user.getNickname())
			(*it)->sendCommand(message.c_str());
	}
}

/**
 * @brief kick user of a channel
 * 
 * @param user the user
 */
void	Channel::kick( User& user ){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->getNickname() == user.getNickname())
		{
			_users.erase(it); // add to ban list?
			return ;
		}	
	}
	return ;
}

/**
 * @brief Remove user of the channel operators
 * 
 * @param user the user to delete
 */
void	Channel::delFromOperatorList( User& user ){
	for (ListUserChannelIterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->getNickname() == user.getNickname())
		{
			_operators.erase(it);
			return ;
		}
	}
	return ;
}

/**
 * @brief Remove user of the channel ban users
 * 
 * @param user the user to delete
 */
void	Channel::delFromBansList( User& user ){
	for (ListUserChannelIterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if ((*it)->getNickname() == user.getNickname())
		{
			_bans.erase(it);
			return ;
		}	
	}
	return ;
}

/**
 * @brief Add user to the channel
 * 
 * @param user the user to add
 */
void	Channel::joinChannel( User& user ){
	_users.push_back(&user);
}

/**
 * @brief Add user to the channel operators
 * 
 * @param user the user to add
 */
void	Channel::addToOperatorList( User& user ){
	_operators.push_back(&user);
}

/**
 * @brief Add user to the channel ban users
 * 
 * @param user the user to add
 */
void	Channel::addToBanList( User& user ){
	if (Channel::isInBanList(user.getNickname()))
		kick(user);
	_bans.push_back(&user);
}





/**
 * @brief Check if a user is in the channel
 * 
 * @param username the username
 * @return true user is in
 * @return false user is not in
 */
bool	Channel::isInChannel( std::string username ){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->getNickname() == username )
			return (true);
	}
	return (false);
}

/**
 * @brief Check if a user is in the channel ban users
 * 
 * @param username the username
 * @return true user is in
 * @return false user is not in
 */
bool		Channel::isInBanList( std::string username ){
	for (ListUserChannelIterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if ((*it)->getNickname() == username )
			return (true);
	}
	return (false);
}

/**
 * @brief Check if a user is in the channel operators
 * 
 * @param username the username
 * @return true user is in
 * @return false user is not in
 */
bool		Channel::isInOperatorList( std::string username ){
	for (ListUserChannelIterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->getNickname() == username )
			return (true);
	}
	return (false);
}



/**
 * @brief Get the channel name
 * 
 * @return std::string the name of the channel
 */
std::string	Channel::getChannelName(){
	return (_channelName);
}

/**
 * @brief Get the channel password
 * 
 * @return std::string the password of the channel
 */
std::string	Channel::getPassword(){
	return (_password);
}

/**
 * @brief Get the visibility / access of the channel
 * 
 * @return true if the channel is private, else false
 */
bool	Channel::getPrivateBool(){
	return (_private);
}


/**
 * @brief Construct a new Channel:: Channel object
 * 
 * @param name name of the channel
 * @param privatebool visibility / access of the channel
 * @param password password of the channel
 */
Channel::Channel( std::string name, bool privatebool, std::string password ) :
				_channelName(name), _private(privatebool), _password(password){   // ajouter pointeur sur user ou user ou ref de user (voir aartiges san)
	std::cout << name << "(channel) private construcor called\n";
};

/**
 * @brief Construct a new Channel:: Channel object
 * 
 * @param name name of the channel
 */
Channel::Channel( std::string name ) : _channelName(name){   // ajouter pointeur sur user ou user ou ref de user (voir aartiges san)
	std::cout << name << "(channel) construcor called\n";
};

/**
 * @brief Destroy the Channel:: Channel object
 */
Channel::~Channel(){
	//delete mes merdes
};