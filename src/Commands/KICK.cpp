#include "Server.hpp"

void irc::KICK(irc::CmdArg& c) {
	if (c.params.size() < 2)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "KICK :Not enough parameters");

	std::vector<std::string> channelNames = ft::split(c.params.at(0), ",");
	const std::string userName = c.params.at(1);

	irc::Channel						*channel;
	std::vector<std::string>::iterator	it;

	for (it = channelNames.begin(); it != channelNames.end(); it++)
	{
		channel = c.server->getChannelByName((*it).substr(1, (*it).length() - 1));
		if (!channel) {
			c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHCHANNEL, *it);
			continue;
		}
		if (c.user != channel->getOperator()) {
			std::string msg = ":" + c.server->getHost() + " " + ERR_CHANOPRIVSNEEDED + " " +  (*it) + " :You're not a channel operator" + "\r\n";
			c.server->sendToClient(c.user->getSocket(), msg);
			continue ;
		}

		irc::User *target = c.server->getUserByNickname(userName);
		if (!target) {
			c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHNICK, userName);
			return ;
		}
		if (channel->contains(target) == false) {
			c.server->sendToClientWithNum(c.user->getSocket(), ERR_USERNOTINCHANNEL, target->getNickname() + " #" + channel->getName() + " :They aren't on that channel");
			continue ;
		}
		if (c.user->getNickname() == target->getNickname()) {
			c.server->sendToClientWithNum(c.user->getSocket(), "", "You are channel operator");
			continue ;
		}

		channel->sendToAllUsers(c, c.getPrefix() + " KICK #" + channel->getName() + " " + target->getNickname() + " " + c.trailing + "\r\n");
		channel->leaveUser(target);
	}
}
