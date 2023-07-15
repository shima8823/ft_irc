#include "Server.hpp"

void irc::PART(irc::CmdArg& c) {
	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "PART :Not enough parameters");

	std::string channelName = c.params.at(0).substr(1, c.params.at(0).length() - 1);
	irc::Channel* channel = c.server->getChannelByName(channelName);

	if (!channel)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOSUCHCHANNEL, channelName);
	if (channel->contains(c.user) == false)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NOTONCHANNEL, channelName + " :You're not on that channel");
	std::string data = c.getPrefix() + " PART #" + channelName + " " + c.trailing + "\r\n";

	channel->sendToAllUsers(c, data);
	c.server->sendToClient(c.user->getSocket(), data);
	channel->leaveUser(c.user);
	if (channel->getUsers().size() == 0)
		c.server->deleteChannel(channel);
}
