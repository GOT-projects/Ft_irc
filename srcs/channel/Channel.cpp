#include "../../includes/includes.hpp"
#include <iostream>

using namespace irc;

void	Channel::changeChanPassword( std::string pass ){
	_password = pass;
}

void	Channel::changeChanTopic( std::string name ){
	_topic = name;
}

void	Channel::changeChanName( std::string name ){
	_channelName = name;
}

void	Channel::giveRights( User& host, User& guest){
	if (this->isInOperatorList(host.getUsername()) && !this->isInBanList(guest.getUsername()))
		this->addToOperatorList(guest);
}

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


void	Channel::sendMessage( std::string message ){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++)
		(*it)->sendCommand(message.c_str());
}

void		Channel::kick( User& user ){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->getUsername() == user.getUsername())
		{
			_users.erase(it); // add to ban list?
			return ;
		}	
	}
	return ;
}

void		Channel::delFromOperatorList( User& user ){
	for (ListUserChannelIterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->getUsername() == user.getUsername())
		{
			_operators.erase(it);
			return ;
		}
	}
	return ;
}

void		Channel::delFromBansList( User& user ){
	for (ListUserChannelIterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if ((*it)->getUsername() == user.getUsername())
		{
			_bans.erase(it);
			return ;
		}	
	}
	return ;
}

void    Channel::joinChannel( User& user ){
	_users.push_back(&user);
}

void		Channel::addToOperatorList( User& user ){
	_operators.push_back(&user);
}

void		Channel::addToBanList( User& user ){
	if (Channel::isInBanList(user.getUsername()))
		kick(user);
	_bans.push_back(&user);
}






bool		Channel::isInChannel( std::string username ){
	for (ListUserChannelIterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it)->getUsername() == username )
			return (true);
	}
	return (false);
}

bool		Channel::isInBanList( std::string username ){
	for (ListUserChannelIterator it = _bans.begin(); it != _bans.end(); it++)
	{
		if ((*it)->getUsername() == username )
			return (true);
	}
	return (false);
}

bool		Channel::isInOperatorList( std::string username ){
	for (ListUserChannelIterator it = _operators.begin(); it != _operators.end(); it++)
	{
		if ((*it)->getUsername() == username )
			return (true);
	}
	return (false);
}




std::string	Channel::getChannelName(){
	return (_channelName);
}

std::string	Channel::getPassword(){
	return (_password);
}

bool	Channel::getPrivateBool(){
	return (_private);
}



Channel::Channel( std::string name, bool privatebool, std::string password ) :
				_channelName(name), _private(privatebool), _password(password){   // ajouter pointeur sur user ou user ou ref de user (voir aartiges san)
	std::cout << name << "(channel) private construcor called\n";
};

Channel::Channel( std::string name ) : _channelName(name){   // ajouter pointeur sur user ou user ou ref de user (voir aartiges san)
	std::cout << name << "(channel) construcor called\n";
};

Channel::~Channel(){
	std::cout << this->_channelName << " destructor called\n";
	//delete mes merdes
};