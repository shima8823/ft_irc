#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <unistd.h>

namespace irc {
	class User {
		private:
			int			socket_;
			std::string	nickname_;
			std::string	username_;
			bool		isAuthorized_;
			bool		isConnected_;
			bool		isResistered_;
			bool		isOperator_;
			bool		isWallops_;

		public:
			User(int sockfd);
			User(User& x);
			~User();

			const int&			getSocket() const { return this->socket_; };
			const std::string&	getNickname() const { return this->nickname_; };
			const std::string&	getUsername() const { return this->username_; };
			bool				getIsConnected() const { return this->isConnected_; };
			bool				getIsAuthorized() const { return this->isAuthorized_; };
			bool				getIsResistered() const { return this->isResistered_; };
			bool				getIsOperator() const { return this->isOperator_; };
			bool				getIsWallops() const { return this->isWallops_; };

			void				setIsConnected(bool status) { this->isConnected_ = status; };
			void				setNickname(std::string nickname) { this->nickname_ = nickname; };
			void				setUsername(std::string username) { this->username_ = username; };
			void				setIsAuthorized(bool status) { this->isAuthorized_ = status; };
			void				setIsResistered(bool status) { this->isResistered_ = status; };
			void				setIsOperator(bool status) { this->isOperator_ = status; };
			void				setIsWallops(bool status) { this->isWallops_ = status; };

			void	print() const;
	};
}

#endif
