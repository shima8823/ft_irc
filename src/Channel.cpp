#include "Channel.hpp"

irc::Channel::Channel(std::string name): name_(name), topic_("") {}

irc::Channel::~Channel() {
	// for (t_users_it it = users_.begin(); it != users_.end(); ++it)
	// 	delete *it;
}

void irc::Channel::newUser(irc::User* user) {
	this->users_.push_back(user);
}

void irc::Channel::leaveUser(irc::User* user) {
	for (t_users_it it = users_.begin(); it != users_.end();) {
		if (*it == user) {
			it = users_.erase(it);
			continue;
		}
		++it;
	}
}

void irc::Channel::sendToAllUsers(CmdArg& c, std::string msg) {
	for (t_users_it it = users_.begin(); it != users_.end(); ++it) {
		c.server->sendToClient((*it)->getSocket(), msg);
	}
}

void irc::Channel::sendToAllOtherUsers(CmdArg& c, std::string msg) {
	for (t_users_it it = users_.begin(); it != users_.end(); ++it) {
		if (c.user->getNickname() != (*it)->getNickname())
			c.server->sendToClient((*it)->getSocket(), msg);
	}
}

bool irc::Channel::contains(irc::User* user) {
	for (t_users_it it = users_.begin(); it != users_.end(); ++it)
	{
		if ((*it)->getNickname() == user->getNickname())
			return true;
	}
	return false;
}

void irc::Channel::print() {
	std::cout << "================CHANNEL===============" << std::endl;
	std::cout << "name: " + getName() << std::endl;

	for (t_users_it it = users_.begin(); it != users_.end(); ++it) {
		std::cout << "user: " + (*it)->getNickname() << std::endl;
	}
	std::cout << "======================================" << std::endl;
}
