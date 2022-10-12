#include "../../includes/includes.hpp"

using namespace irc;


void    Channel::joinChannel(){
	
}

void    Channel::inviteToChannel(){  // args: invité, invitant
	//if invitant peut inviter et mode le permet
		//if invité peut etre invite (pas blacklister)
			//ft_join
}



Channel::Channel( std::string name, bool privatebool, std::string password ) :
				_channelName(name), _private(privatebool), _password(password){   // ajouter pointeur sur user ou user ou ref de user (voir aartiges san)
	std::cout << name << "(channel) construcor called\n";
	if (privatebool)
		std::cout << "It's a private channel.\n";
//	this->_mods = 
};

Channel::~Channel(){
	std::cout << this->_channelName << " destructor called\n";
	//delete mes merdes
};