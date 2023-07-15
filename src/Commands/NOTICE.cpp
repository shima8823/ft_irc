#include "Server.hpp"

void irc::NOTICE(irc::CmdArg& c) {
	std::string target = c.params.at(0);

	if ( target.at(0) == '#') {
		Channel* channel = c.server->getChannelByName(target.substr(1, target.length() - 1));
		if (channel) {
			std::string msg = c.getPrefix() + " NOTICE #" + channel->getName() + " :" + c.trailing + "\r\n";
			channel->sendToAllOtherUsers(c, msg);
			return;
		}
	}

	irc::User *user = c.server->getUserByNickname(target); 
	if (!user)
		return ;
	std::string msg = c.getPrefix() + " NOTICE " + target + " :" + c.trailing + "\r\n";
	c.server->sendToClient(user->getSocket(), msg);
}
