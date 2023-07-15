#include "Server.hpp"

void irc::MODE(CmdArg& c) {
	if (c.params.size() < 2)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "MODE :Not enough parameters");

	std::string targetNickname = c.params.at(0);
	
	if (targetNickname.at(0) == '#')
		return ;

	if (c.user->getIsOperator()) {
		if (c.server->getUserByNickname(targetNickname) == NULL) {
			c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHNICK, targetNickname);;
			return ;
		}
	} else {
		if (c.user->getNickname() != targetNickname) {
			c.server->sendToClientWithNum(c.user->getSocket(), ERR_USERSDONTMATCH, ":Cannot change mode for other users");
			return ;
		}
	}

	irc::User* target = c.server->getUserByNickname(targetNickname);
	std::string data;

	for (size_t i = 1; i < c.params.size(); i++)
	{
		if (c.params.at(i).find("+w") != std::string::npos && c.user->getIsOperator()) {
			target->setIsWallops(true);
			data = c.getPrefix() + " MODE " + targetNickname + " " + "+w" + "\r\n";
			c.server->sendToClient(target->getSocket(), data);
		}

		if (c.params.at(i).find("-o") != std::string::npos) {
			target->setIsOperator(false);
			data = c.getPrefix() + " MODE " + targetNickname + " " + "-o" + "\r\n";
			c.server->sendToClient(target->getSocket(), data);
		}

		if (c.params.at(i).find("-w") != std::string::npos) {
			target->setIsWallops(false);
			data = c.getPrefix() + " MODE " + targetNickname + " " + "-w" + "\r\n";
			c.server->sendToClient(target->getSocket(), data);
		}
	}
}
