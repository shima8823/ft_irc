# include "Server.hpp"

void irc::PRIVMSG(irc::CmdArg& c) {
	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "PRIVMSG :Not enough parameters");

	ft::put("PRIVMSG");
	std::string target = c.params.at(0);

	if ( target.at(0) == '#') {
		Channel* channel = c.server->getChannelByName(target.substr(1, target.length() - 1));
		if (channel) {
			std::string data = c.getPrefix() + " PRIVMSG #" + channel->getName() + " " + c.trailing + "\r\n";
			channel->sendToAllOtherUsers(c, data);
			return;
		}
	} else {
		t_users users = c.server->getUsers();
		for (t_users_it it = users.begin(); it != users.end(); ++it ) {
			if ( (*it)->getNickname() == target ) {
				std::string data = c.getPrefix() + " PRIVMSG " + target + " " + c.trailing + "\r\n";
				c.server->sendToClient((*it)->getSocket(), data);
				return;
			}
		}
	}
	std::cerr << "no such target." << std::endl;
}
