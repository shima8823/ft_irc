#include "Server.hpp"

static bool isInvalidName(const std::string& name) {
	if (name.find_first_of("#,") != std::string::npos
		|| name.length() == 0)
		return true;
	return false;
}

void irc::JOIN(irc::CmdArg& c) {
	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NEEDMOREPARAMS, "JOIN :Not enough parameters");

	std::string name = c.params.at(0).substr(1, c.params.at(0).length() - 1);

	if (isInvalidName(name))
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_BADCHANMASK, "#" + name + " :Bad Channel Mask");

	t_channels channels = c.server->getChannels();
	std::string msg = c.getPrefix() + " JOIN #" + name + "\r\n";
	if (channels.size() != 0) {
		for (t_channels_it it = channels.begin(); it != channels.end(); ++it) {
			if ((*it)->getName() == name) {
				(*it)->newUser(c.user);
				(*it)->sendToAllUsers(c, msg);
				if ((*it)->getTopic().length())
					c.server->sendToClientWithNum(c.user->getSocket(), RPL_TOPIC, c.params.at(0) + " " + (*it)->getTopic());
				return ;
			}
		}
	}

	irc::Channel* newChannel = c.server->createChannel(name);
	newChannel->setOperator(c.user);
	newChannel->newUser(c.user);
	c.server->sendToClient(c.user->getSocket(), msg);
}
