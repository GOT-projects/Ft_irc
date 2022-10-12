#pragma once

#include "../includes.hpp"

namespace irc { 
	class Mods {
        public:
           	bool        _privateChannel;	//p - private channel flag;
           	bool        _secretChannel; 	//s - secret channel flag;
           	bool        _inviteOnly;    	//i - invite-only channel flag;
           	bool        _nameTopicByOper;	//t - topic settable by channel operator only flag;
           	    	//n - no messages to channel from clients on the outside;
           	bool   	    _moderatedChannel;
           	
            void        operPrivileges();    //o - give/take channel operator privileges;
            void        setUserLimits(); 
           	void        setBanMask();    	//b - set a ban mask to keep users out;
           	void        moderatorStatus();    	//v - give/take the ability to speak on a moderated channel;
           	void        setChannelPassword();    	//k - set a channel key (password).
			  
			//When using the 'o' and 'b' options, a restriction on a total of three
   			//per mode command has been imposed.  That is, any combination of 'o'
   			//and
    };
}
