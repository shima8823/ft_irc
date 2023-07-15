#include "Server.hpp"

void irc::PING(irc::CmdArg& c) {
	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "PING :Not enough parameters");

	std::string msg = ":" + c.server->getHost() + " PONG :" + c.params.at(0) + "\r\n";

	c.server->sendToClient(c.user->getSocket(), msg);
}
