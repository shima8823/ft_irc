# include "Server.hpp"

void irc::TOPIC(irc::CmdArg& c) {
	if (c.params.size() == 0) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "TOPIC :Not enough parameters");
		return ;
	}

	std::string channelName = c.params.at(0);
	if (channelName.at(0) != '#') {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHCHANNEL, channelName);
		return ;
	}

	irc::Channel *channel = c.server->getChannelByName(channelName.substr(1, channelName.length() - 1));
	if (!channel) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHCHANNEL, channelName);
		return ;
	}

	if (!channel->contains(c.user)) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
		return ;
	}

	if (c.user == channel->getOperator()) {
		channel->setTopic(c.trailing);
		std::string msg = c.getPrefix() + " TOPIC " + channelName + " :" + c.trailing + "\r\n";
		channel->sendToAllUsers(c, msg);
	} else {
		std::string msg = ":" + c.server->getHost() + " " + ERR_CHANOPRIVSNEEDED + " " +  channelName + " :You're not a channel operator" + "\r\n";
		c.server->sendToClient(c.user->getSocket(), msg);
	}
}
