#include "Server.hpp"

__attribute__((destructor))
static void d() {
	std::cout << "===== leaks =====" << std::endl;
	system("leaks -q ircserv");
}

bool flag = true;

void signalHandler(int sig) {
	if (sig == SIGINT)
		flag = false;
}

int main(int argc, char **argv) {
	try {
		if (argc != 3)
			throw std::runtime_error("Invalid arguments: ./ircserv [PORT] [PASSWORD]");

		irc::Server server("127.0.0.1", std::atoi(argv[1]), static_cast<std::string>(argv[2]));

		server.initServer();

		if (signal(SIGINT, &signalHandler) == SIG_ERR)
			throw std::runtime_error("signal(): ");

		while(flag)
			server.loop();

	} catch (std::exception& e) {
		std::cerr << e.what() << (errno ? std::strerror(errno) : "") << std::endl;
		exit(1);
	}
	return 0;
}
