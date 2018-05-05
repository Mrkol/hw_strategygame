#include "network.hpp"

namespace Network
{
	int test()
	{
		server();
		client();
		return 0;
	}

	int server() {
		rpc::server srv(8080);

		srv.bind("echo", [](std::string const& s) {
			return std::string("> ") + s;
		});

		srv.run();
		return 0;
	}


	int client() {
		rpc::client c("localhost", 8080);

		std::string input, result;
		while (std::getline(std::cin, input)) {
			if (!input.empty()) {
				result = c.call("echo", input).as<std::string>();
				std::cout << result << std::endl;
			}
		}
		return 0;
	}
	
}
