#include "Server.hpp"

void irc::PASS(CmdArg& c) {
	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "PASS :Not enough parameters");
	if (c.user->getIsResistered() == true)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_ALREADYREGISTERED, "PASS: You are already resisterd.");
	if (c.params.at(0) != c.server->getPasswd()) {
		std::cout << "wrong password." << std::endl;
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_PASSWDMISSMATCH, "wrong password.");
		c.user->setIsConnected(false);
		return ;
	}

	c.user->setIsAuthorized(true);
	std::cout << GRN << "Socket " << c.user->getSocket() << " was authorized!" << DEF << std::endl;
}
