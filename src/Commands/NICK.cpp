#include "Server.hpp"

static bool isInvalidNick(const std::string& nickname) {
	if (nickname.find_first_of("+-#,") != std::string::npos
		|| nickname.length() == 0)
		return true;
	return false;
}

void irc::NICK(CmdArg& c) {
	if (c.user->getIsAuthorized() == false)
		return ;

	if (c.params.size() == 0)
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_NONICKNAMEGIVEN, ":No nickname given");

	std::string nickname = c.params.at(0);

	if (isInvalidNick(nickname))
		return c.server->sendToClientWithNum(c.user->getSocket(), ERR_ERRONEUSNICKNAME, nickname + " :Erroneous nickname");

	t_users users = c.server->getUsers();
	t_users_it it;
	std::string msg;
	for (it = users.begin(); it != users.end(); ++it) {
		if (c.user != *it && nickname == (*it)->getNickname())
		{
			std::cout << "already in use" << std::endl;
			msg = ":" + c.server->getHost() + " " + ERR_NICKNAMEINUSE + " * " + nickname + " :Nickname is already in use\r\n";
			c.server->sendToClient(c.user->getSocket(), msg);
			return ;
		}
	}

	std::size_t prevLength = c.user->getNickname().length();

	msg = ":" + (prevLength > 0 ? c.user->getNickname() : nickname);
	msg += "!" + c.user->getUsername() + "@" + c.server->getHost();
	msg += " NICK :" + nickname + "\r\n";
	c.server->sendToClient(c.user->getSocket(), msg);
	c.user->setNickname(nickname);

	if (prevLength == 0 && c.user->getIsResistered())
		c.sendRegistrationMsg();
}
