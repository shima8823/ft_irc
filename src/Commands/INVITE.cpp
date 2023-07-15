#include "Server.hpp"

void irc::INVITE(irc::CmdArg& c) {
	if (c.params.size() < 2)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "INVITE :Not enough parameters");

	std::string userName = c.params.at(0);
	std::string channelName = c.params.at(1).substr(1, c.params.at(1).length() - 1);

	irc::User *target = c.server->getUserByNickname(userName);
	if (!target) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHNICK, userName);
		return ;
	}

	irc::Channel *channel = c.server->getChannelByName(channelName);
	if (!channel) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHCHANNEL, channelName);
		return ;
	}

	if (channel->contains(c.user) == false) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
		return ;
	}
	if (channel->contains(target)) {
		c.server->sendToClientWithNum(c.user->getSocket(), ERR_USERONCHANNEL, target->getNickname() + " #" + channelName + " :is already on channel");
		return ;
	}

	c.server->sendToClientWithNum(c.user->getSocket(), RPL_INVITING, target->getNickname() + " #" + channelName);
	std::string msg = c.getPrefix() + " INVITE " + target->getNickname() + " #" +  channelName + "\r\n";
	c.server->sendToClient(target->getSocket(), msg);
}
