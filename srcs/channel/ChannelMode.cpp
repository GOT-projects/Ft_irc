#include "../../includes/includes.hpp"

using namespace irc;

void		Mods::changeTopicFlag( void ){
	if (_topicFlag == true)
		_topicFlag = false;
	else if (_topicFlag == false)
		_topicFlag = false;
}

void		Mods::changeTopicFlag(bool status){
	_topicFlag = status;
}

void		Mods::changeSecretFlag( void ){
	if (_secretFlag == true)
		_secretFlag = false;
	else if (_secretFlag == false)
		_secretFlag = false;
}

void		Mods::changeSecretFlag(bool status){
	_secretFlag = status;
}

void		Mods::changeInviteFlag( void ){
	if (_inviteOnly == true)
		_inviteOnly = false;
	else if (_inviteOnly == false)
		_inviteOnly = false;
}

void		Mods::changeInviteFlag(bool status){
	_inviteOnly = status;
}
