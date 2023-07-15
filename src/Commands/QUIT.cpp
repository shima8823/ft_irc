#include "Server.hpp"

void irc::QUIT(CmdArg& c) {
	std::string msg = c.getPrefix() + " QUIT :Quit: " + c.trailing + "\r\n" + "ERROR :Quit: " + c.trailing + "\r\n"; 
	c.server->sendToClient(c.user->getSocket(), msg);
	c.forcedLeaveChannels(c.user);
	c.user->setIsConnected(false);
}
