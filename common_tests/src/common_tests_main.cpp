#include "common_tests_main.hpp"
#include <iostream>
#include "gtest/gtest.h"
#include "MatchManager.hpp"
#include "Network/network.hpp"
#include "Network\Client.hpp"
#include "Network\Server.hpp"

int main(int argc, char* argv[])
{
	int t;
	std::cin >> t;
	if (t == 0)
	{
		std::cout << "I am server\n";
		Common::Network::CGameServer server({"127.0.0.1"}, 8080);
		Common::MatchManager* manager = new Common::MatchManager();
		while (std::cin >> t)
		{
			if (t)
			{
				server.SynchronizeClients(manager);
			}
			else
			{
				server.StopClient(0);
			}
			
		}
	}
	else
	{
		std::cout << "I am client\n";
		Common::Network::CGameClient client(8080);

		//client.SetAmountOfThreads(2);
		client.Start();

	}
	std::cin >> t;
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
