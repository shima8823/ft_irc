#include "Server.hpp"

irc::Server::Server(std::string host, int port, std::string passwd) : operatorPasswd_("admin") {
	this->host_ = host;
	this->port_ = port;
	this->passwd_ = passwd;
	FD_ZERO(&(this->sockfds_));
	FD_ZERO(&(this->tmpSockfds_));

	this->commandFuncs_["PASS"] = &PASS;
	this->commandFuncs_["NICK"] = &NICK;
	this->commandFuncs_["USER"] = &USER;
	this->commandFuncs_["motd"] = &MOTD;
	this->commandFuncs_["PING"] = &PING;
	this->commandFuncs_["JOIN"] = &JOIN;
	this->commandFuncs_["PRIVMSG"] = &PRIVMSG;
	this->commandFuncs_["PART"] = &PART;
	this->commandFuncs_["OPER"] = &OPER;
	this->commandFuncs_["kill"] = &KILL;
	this->commandFuncs_["TOPIC"] = &TOPIC;
	this->commandFuncs_["MODE"] = &MODE;
	this->commandFuncs_["wallops"] = &WALLOPS;
	this->commandFuncs_["KICK"] = &KICK;
	this->commandFuncs_["INVITE"] = &INVITE;
	this->commandFuncs_["QUIT"] = &QUIT;
	this->commandFuncs_["NOTICE"] = &NOTICE;

	std::cout << GRN << "IRC Server starts on port: " << ULINE << BOLD << port << RESET << DEF << std::endl;
}

irc::Server::~Server() {
	close(this->socket_);
	for (t_users_it it = this->users_.begin(); it != this->users_.end(); ++it)
		delete *it;
	if (channels_.size()) {
		for (t_channels_it it = this->channels_.begin(); it != this->channels_.end(); ++it)
			delete *it;
	}
	std::cout << MGN_S("Bye!") << std::endl;
}

void irc::Server::initServer() {

	this->socket_ = socket(AF_INET, SOCK_STREAM, 0);
	if ( this->socket_ < 0 )
		throw std::runtime_error("socket(): ");

	int opt = 1;
	if ( setsockopt(this->socket_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0)
		throw std::runtime_error("setsockopt(): ");

	struct sockaddr_in addr;
	bzero(&addr, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(this->port_);

	if ( bind(this->socket_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0 )
		throw std::runtime_error("bind(): ");

	if ( listen(this->socket_, SOMAXCONN) != 0 )
		throw std::runtime_error("listen(): ");

	this->maxfd_ = this->socket_;
	FD_SET(this->socket_, &(this->sockfds_));

	if (fcntl(this->socket_, F_SETFL, O_NONBLOCK) < 0)//ノンブロック化
		throw std::runtime_error("fcntl(): ");
}

void irc::Server::loop() {
	int res;
	if ( (res = acceptClient()) != -1) {
		createNewUser(res);
	}

	std::memmove(&(this->tmpSockfds_), &(this->sockfds_), sizeof(fd_set));

	if ( select( this->maxfd_ + 1, &this->tmpSockfds_, NULL, NULL, NULL) == -1)
		return ;

	t_users_it it;
	for (it = this->users_.begin(); it != this->users_.end(); ++it) {

		int clientSockfd = (*it)->getSocket();
		if ( FD_ISSET(clientSockfd, &(this->tmpSockfds_)) ) {
			char buff[BUFFER_SIZE];
			bzero(buff, BUFFER_SIZE);

			ssize_t l;
			if ( (l = recv(clientSockfd, buff, BUFFER_SIZE, MSG_DONTWAIT)) == 0 )
				(*it)->setIsConnected(false);
			else if ( l != -1 ) {
				executeCommand(clientSockfd, static_cast<std::string>(buff));
			}
		}

		if ( (*it)->getIsConnected() == false ) {
			deleteClient(*it);
			break ;
		}
	}
}

int irc::Server::acceptClient() {
	struct sockaddr_in client_addr;
	bzero(&client_addr, sizeof(sockaddr_in));
	socklen_t len = sizeof(sockaddr_in);

	return ( accept(this->socket_, reinterpret_cast<sockaddr*>(&client_addr), &len) ); //ノンブロッキングだからクライアントが来ない場合は -1 でreturn
}

void irc::Server::createNewUser(int clientSockfd) {
	if (clientSockfd > this->maxfd_)
			this->maxfd_ = clientSockfd;

	this->users_.push_back(new irc::User(clientSockfd));
	FD_SET(clientSockfd, &(this->sockfds_));
}

void irc::Server::deleteClient(irc::User* target) {
	FD_CLR(target->getSocket(), &(this->sockfds_));

	for (t_users_it it = users_.begin(); it != users_.end();) {
		if (*it == target) {
			it = users_.erase(it);
			continue;
		}
		++it;
	}

	std::cout << target->getSocket() << " is Disconnected." << std::endl;
	close(target->getSocket());
	delete target;
}

irc::User* irc::Server::getUserBySockfd(int sockfd) {
	t_users_it it;

	for ( it = this->users_.begin(); it != this->users_.end(); ++it ) {
		if ( (*it)->getSocket() == sockfd ) {
			return *it;
		}
	}
	return NULL;
}

irc::User* irc::Server::getUserByNickname(std::string nickname) {
	t_users_it it;

	for ( it = this->users_.begin(); it != this->users_.end(); ++it ) {
		if ( (*it)->getNickname() == nickname ) {
			return *it;
		}
	}
	return NULL;
}

void irc::Server::sendToClient(int clientSockfd, std::string msg) {
	std::cout << "Send to [" << getUserBySockfd(clientSockfd)->getNickname() << "] Data: <" << CYN << msg.substr(0, msg.length() - 2) << DEF << ">" << std::endl;

	send(clientSockfd, msg.c_str(), msg.length(), 0);
}

void irc::Server::sendToClientWithNum(int clientSockfd, std::string NUM, std::string msg) {
	std::string data;

	data += ":" + this->host_ + " " + NUM + " ";
	data += getUserBySockfd(clientSockfd)->getNickname();
	data += " " + msg + "\r\n";

	sendToClient(clientSockfd, data);
}

void irc::Server::sendToAllUsers(std::string msg) {
	t_users_it	it;

	for (it = users_.begin(); it != users_.end(); ++it) {
		sendToClient((*it)->getSocket(), msg);
	}
}

void irc::Server::executeCommand(int clientSockfd, std::string buff) {
	std::vector<std::string> cmds;

	cmds = ft::split(buff, "\r\n");
	std::cout << "cmds = " << cmds << std::endl;

	if (cmds[0][0] == '?') { //ncでの情報表示用
		info(cmds[0]);
		return ;
	}

	for (uint32 i = 0; i < cmds.size(); i++) {
		
		std::vector<std::string> elems;
		elems = ft::split(cmds.at(i), " ");

		std::string cmd = elems[0];
		elems.erase(elems.begin());

		std::cout << getUserBySockfd(clientSockfd)->getNickname() << ": " << "[" << cmd << "] " << elems << std::endl;

		CmdArg* arg = new CmdArg(this, getUserBySockfd(clientSockfd), elems);

		std::size_t pos = cmds.at(i).find(":");
		if (pos != std::string::npos)
			arg->trailing = cmds.at(i).erase(0, pos);

		try {
			commandFuncs_.at(cmd)(*arg);
		} catch(const std::exception& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << RED << "Error: " << cmd << " not exists." << DEF << std::endl;
		}

		delete arg;
	}
}

irc::Channel* irc::Server::createChannel(std::string name) {
	irc::Channel* newChannel = new irc::Channel(name);
	this->channels_.push_back(newChannel);

	for (t_channels_it it = this->channels_.begin(); it != this->channels_.end(); ++it) {
		std::cout << "Channel: " << (*it)->getName() << std::endl;
	}
	return newChannel;
}

void irc::Server::deleteChannel(irc::Channel* target) {
	for (t_channels_it it = channels_.begin(); it != channels_.end();) {
		if (*it == target) {
			it = channels_.erase(it);
			continue;
		}
		++it;
	}
	delete target;
}

irc::Channel* irc::Server::getChannelByName(std::string name) {
	t_channels_it	it;

	for (it = channels_.begin(); it != channels_.end(); ++it) {
		if ((*it)->getName() == name)
			return (*it);
	}

	return NULL;
}

void irc::Server::info(std::string cmd) {
	std::cout << "INFO: " << cmd.substr(1, cmd.length() - 1) << std::endl;

	if (cmd == "?user") {
		size_t i=1;
		for (t_users_it it = users_.begin(); it != users_.end(); ++it) {
			std::cout << "id: " << i++ << std::endl;
			(*it)->print();
		}
	} else if (cmd == "?channel") {
		for (t_channels_it it = channels_.begin(); it != channels_.end(); ++it) {
			(*it)->print();
		}
	}
}
