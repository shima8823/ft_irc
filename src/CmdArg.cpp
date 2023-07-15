#include "CmdArg.hpp"

std::string irc::CmdArg::getPrefix() const {
	std::string res = ":" + this->user->getNickname();
	res += "!" + this->user->getUsername();
	res += "@" + this->server->getHost();
	return res;
}

void irc::CmdArg::sendRegistrationMsg() {
	irc::MOTD(*this);
	std::string info = "Nickname: " + this->user->getNickname() + "\nUsername: " + this->user->getUsername();
	this->server->sendToClientWithNum(this->user->getSocket(), RPL_WELCOME, GRN_S("Welcome to ft_irc server!"));
	this->server->sendToClientWithNum(this->user->getSocket(), RPL_YOURHOST, GRN_S("Your host is " + std::string(BOLD) + this->server->getHost()));
	this->server->sendToClientWithNum(this->user->getSocket(), RPL_CREATED, "This server is created by tharaguc");
	this->server->sendToClientWithNum(this->user->getSocket(), RPL_MYINFO, info);
	this->server->sendToClientWithNum(this->user->getSocket(), RPL_NONE, "======================================");
}

void irc::CmdArg::forcedLeaveChannels(User* target) {
	t_channels channels = this->server->getChannels();
	for (t_channels_it it = channels.begin(); it != channels.end(); ++it) {
		if ((*it)->contains(target) == false)
			continue;
		(*it)->leaveUser(target);
		if ((*it)->getUsers().size() == 0) {
			this->server->deleteChannel(*it);
		} else {
			(*it)->sendToAllUsers(*this, this->getPrefix() + " QUIT " + ":Killed: (" + this->user->getNickname() + " " + this->trailing + ") #" + (*it)->getName() + "\r\n");
		}
	}
}
