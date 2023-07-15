#ifndef DEFINITION_HPP
# define DEFINITION_HPP

# include <iostream>
# include <fstream>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h> 
# include <unistd.h>
# include <fcntl.h>
# include <vector>
# include <map>
# include <list>
# include <algorithm>

// IRC Numerics
# define RPL_WELCOME			"001"
# define RPL_YOURHOST			"002"
# define RPL_CREATED			"003"
# define RPL_MYINFO				"004"
# define RPL_NONE				"300"

# define RPL_WHOISREGNICK		"307"

# define RPL_MOTD				"372"
# define RPL_MOTDSTART			"375"
# define RPL_ENDOFMOTD			"376"
# define ERR_NOMOTD				"422"
# define ERR_PASSWDMISSMATCH	"464"
# define ERR_ALREADYREGISTERED	"462"

# define RPL_UMODEIS			"221"
# define RPL_NOTOPIC			"331"
# define RPL_TOPIC				"332"
# define RPL_INVITING			"341"
# define RPL_YOUREOPER			"381"
# define ERR_NOSUCHNICK			"401"
# define ERR_NOSUCHCHANNEL		"403"
# define ERR_NONICKNAMEGIVEN	"431"
# define ERR_ERRONEUSNICKNAME	"432"
# define ERR_NICKNAMEINUSE		"433"
# define ERR_USERNOTINCHANNEL	"441"
# define ERR_NOTONCHANNEL		"442"
# define ERR_USERONCHANNEL		"443"
# define ERR_NEEDMOREPARAMS		"461"
# define ERR_BADCHANMASK		"476"
# define ERR_NOPRIVILEGES		"481"
# define ERR_CHANOPRIVSNEEDED	"482"
# define ERR_NOOPERHOST			"491"
# define ERR_USERSDONTMATCH		"502"

# define S(c) std::string(c)

// color settings
# define DEF	"\x1b[39m"
# define BLK_S(s)	S("\x1b[30m") + S(s) + S(DEF)
# define RED_S(s)	S("\x1b[31m") + S(s) + S(DEF)
# define GRN_S(s)	S("\x1b[32m") + S(s) + S(DEF)
# define YEL_S(s)	S("\x1b[33m") + S(s) + S(DEF)
# define BLU_S(s)	S("\x1b[34m") + S(s) + S(DEF)
# define MGN_S(s)	S("\x1b[35m") + S(s) + S(DEF)
# define CYN_S(s)	S("\x1b[36m") + S(s) + S(DEF)

# define BLK "\x1b[30m"
# define RED "\x1b[31m"
# define GRN "\x1b[32m"
# define YEL "\x1b[33m"
# define BLU "\x1b[34m"
# define MGN "\x1b[35m"
# define CYN "\x1b[36m"

# define BLK_B "\x1b[40m"
# define RED_B "\x1b[41m"
# define GRN_B "\x1b[42m"
# define YEL_B "\x1b[43m"
# define BLU_B "\x1b[44m"
# define MGN_B "\x1b[45m"
# define CYN_B "\x1b[46m"
# define DEF_B	"\x1b[99m"

# define BOLD "\x1b[1m"
# define ULINE "\x1b[4m"
# define RESET "\x1b[0m"

// types
typedef int				int32;
typedef unsigned int	uint32;
typedef long			int64;
typedef unsigned long	uint64;

namespace irc {
	class User;
	class Channel;

	typedef std::list<irc::User*>				t_users;
	typedef std::list<irc::User*>::iterator		t_users_it;
	typedef std::list<irc::Channel*>			t_channels;
	typedef std::list<irc::Channel*>::iterator	t_channels_it;
}

// utilities
namespace ft {

	// utility functions
	std::vector<std::string>	split(std::string str, std::string delim);
	void						put(std::string s);

}

// utility operators
std::ostream& operator << (std::ostream& stream, std::vector<std::string>& strs);

#endif
