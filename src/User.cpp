#include "User.hpp"
#include "definition.hpp"

irc::User::User(int sockfd) {
	this->socket_ = sockfd;
	this->isConnected_ = true;
	this->isAuthorized_ = false;
	this->isResistered_ = false;
	this->nickname_ = "";
	this->isOperator_ = false;
	this->isWallops_ = false;
}

irc::User::User(User& x) {
	this->socket_ = x.socket_;
	this->isConnected_ = x.isConnected_;
	this->isAuthorized_ = x.isAuthorized_;
	this->nickname_ = x.nickname_;
}

irc::User::~User() {}

void irc::User::print() const {
	std::cout << "================USER===============\n";
	std::cout << "Nickname  -> " << this->nickname_ << std::endl;
	std::cout << "Socket    -> " << this->socket_ << std::endl;
	std::cout << "Connected -> " << (this->isConnected_ ? (GRN_S("YES")) : (RED_S("NO"))) << std::endl;
	std::cout << "===================================\n";
}
