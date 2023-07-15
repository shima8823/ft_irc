#ifndef CMDARG_HPP
# define CMDARG_HPP

# include "Server.hpp"

namespace irc {
	class Server;

	class CmdArg {
		private:
		public:
			Server*						server;
			User*						user;
			std::vector<std::string>&	params;
			std::string					trailing;

			CmdArg(irc::Server* s, irc::User* u, std::vector<std::string>& p): server(s), user(u), params(p), trailing("") {};
			~CmdArg() {};

			std::string	getPrefix() const;
			void		sendRegistrationMsg();
			void		forcedLeaveChannels(User* target);

	};
}

#endif
