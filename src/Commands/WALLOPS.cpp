#include "Server.hpp"

void irc::WALLOPS(irc::CmdArg& c) {
	if (!c.user->getIsOperator()) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOPRIVILEGES, ":Permission Denied- You're not an IRC operator");
		return ;
	}
	
	t_users users = c.server->getUsers();
	for (t_users_it it = users.begin(); it != users.end(); ++it ) {
		if ((*it)->getIsWallops()) {
			std::string data = ":" + c.server->getHost() + " WALLOPS " + c.trailing + "\r\n";
			c.server->sendToClient((*it)->getSocket(), data);
		}
	}	
}
