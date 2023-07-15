#include "Server.hpp"

void irc::OPER(CmdArg& c) {

	if (c.params.size() < 2)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "OPER :Not enough parameters");

	std::string userName = c.params.at(0);

	if (c.user->getNickname() != userName) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOOPERHOST, ":No O-lines for your host");
		return ;
	}

	if (c.params.at(1) == c.server->getOperatorPasswd()) {
		c.user->setIsOperator(true);
		std::string data = c.getPrefix() + " MODE " + userName + " " + "+o" + "\r\n";
		c.server->sendToClient(c.user->getSocket(), data);
		c.server->sendToClientWithNum(c.user->getSocket(), RPL_YOUREOPER, ":You are now an IRC operator");
	} else {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_PASSWDMISSMATCH, ":Password incorrect");
	}
}
