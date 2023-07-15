#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Server.hpp"
# include "definition.hpp"

namespace irc {
	class CmdArg;

	class Channel {
		private:
			std::string		name_;
			t_users			users_;
			irc::User*		channelOperator_;
			std::string		topic_;

		public:
			Channel(std::string name);
			~Channel();

			void		setName(std::string name) { this->name_ = name; };
			void		setOperator(irc::User* user) { this->channelOperator_ = user; };
			void		setTopic(std::string topic) { this->topic_ = topic; };

			std::string	getName() const { return this->name_; };
			t_users		getUsers() const { return this->users_; };
			irc::User*	getOperator() const { return this->channelOperator_; };
			std::string	getTopic() const { return this->topic_; };

			void	newUser(irc::User* newUser);
			void	leaveUser(irc::User* user);

			void	sendToAllUsers(CmdArg& c, std::string msg);
			void	sendToAllOtherUsers(CmdArg& c, std::string msg);
			bool	contains(irc::User* user);

			void	print();
	};

}

#endif
