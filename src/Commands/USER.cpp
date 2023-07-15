#include "Server.hpp"

void irc::USER(irc::CmdArg& c) {
	if (c.user->getIsAuthorized() == false)
		return ;

	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "USER :Not enough parameters");

	c.user->setUsername(c.params.at(0));
	c.user->setIsResistered(true);

	if (c.user->getNickname().length() > 0)
		c.sendRegistrationMsg();
}
