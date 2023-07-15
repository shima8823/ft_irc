#include "Server.hpp"

void irc::KILL(CmdArg& c) {
	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "KILL :Not enough parameters");

	if (!c.user->getIsOperator()) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOPRIVILEGES, ":Permission Denied- You're not an IRC operator");
		return ;
	}
	irc::User *target = c.server->getUserByNickname(c.params.at(0));
	if (!target) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHNICK, c.params.at(0));;
		return ;
	}

	std::string msg = c.getPrefix() + " KILL " + target->getNickname() + " " + c.trailing + "\r\n";
	c.server->sendToClient(target->getSocket(), msg);
	c.forcedLeaveChannels(target);

	target->setIsConnected(false);
}
