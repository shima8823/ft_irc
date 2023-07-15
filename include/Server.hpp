#ifndef SERVER_HPP
# define SERVER_HPP

# include "definition.hpp"
# include "User.hpp"
# include "Channel.hpp"
# include "CmdArg.hpp"

# define BUFFER_SIZE 512

namespace irc {

	class CmdArg;
	class Channel;

	class Server {

		private:
			int			socket_;
			std::string	host_;
			int			port_;
			std::string	passwd_;

			int			maxfd_;

			struct fd_set	sockfds_;
			struct fd_set	tmpSockfds_;

			t_users		users_;
			t_channels	channels_;

			std::map<std::string, void (*)(CmdArg&)> commandFuncs_;

			const std::string operatorPasswd_;

		public:
			Server(std::string host, int port, std::string passwd);
			~Server();

			const int&			getSockfd() const { return this->socket_; };
			const std::string&	getPasswd() const { return this->passwd_; };
			const std::string&	getHost() const { return this->host_; };
			t_users				getUsers() const { return this->users_; };
			t_channels			getChannels() const { return this->channels_; };
			const std::string&	getOperatorPasswd() const { return this->operatorPasswd_; };

			void	initServer();
			void	loop();
			int		acceptClient();
			void	createNewUser(int clientSockfd);
			void	deleteClient(irc::User* target);
			void	sendToClient(int clientSockfd, std::string msg);
			void	sendToClientWithNum(int clientSockfd, std::string NUM, std::string msg);
			void	sendToAllUsers(std::string msg);
			irc::User*	getUserBySockfd(int sockfd);
			irc::User*	getUserByNickname(std::string nickname);

			void	executeCommand(int clientScokfd, std::string buff);

			// Channel
			irc::Channel*	createChannel(std::string name);
			void			deleteChannel(irc::Channel* target);
			irc::Channel*	getChannelByName(std::string name);

			void	info(std::string cmd);

	};

	// Commands
	void	NICK(CmdArg& c);
	void	PASS(CmdArg&);
	void	USER(irc::CmdArg& c);
	void	MOTD(irc::CmdArg& c);
	void	PING(irc::CmdArg& c);
	void	PRIVMSG(irc::CmdArg& c);
	void	JOIN(irc::CmdArg& c);
	void	PART(irc::CmdArg& c);
	void	OPER(irc::CmdArg& c);
	void	KILL(irc::CmdArg& c);
	void	TOPIC(irc::CmdArg& c);
	void	MODE(irc::CmdArg& c);
	void	WALLOPS(irc::CmdArg& c);
	void	KICK(irc::CmdArg& c);
	void	INVITE(irc::CmdArg& c);
	void	QUIT(irc::CmdArg& c);
	void	NOTICE(irc::CmdArg& c);

}

#endif
