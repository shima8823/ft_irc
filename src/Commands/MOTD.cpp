#include "Server.hpp"

void irc::MOTD(irc::CmdArg& c) {
	std::string motdstr;
	std::ifstream ifs("config/MOTD.conf");
	if ( ifs.fail() )
		std::cerr << "Couldn't open MOTD file." << std::endl;

	motdstr = std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>()) + "\r\n";

	c.server->sendToClientWithNum(c.user->getSocket(), RPL_MOTD, motdstr);

	ifs.close();
}
