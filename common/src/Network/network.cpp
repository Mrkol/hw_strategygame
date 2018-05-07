#include "Network/network.hpp"

namespace Network
{
	namespace Test
	{
		void foo() {
			std::cout << "foo was called!" << std::endl;
		}

		int server() {
			// Creating a server that listens on port 8080
			rpc::server srv(8080);

			// Binding the name "foo" to free function foo.
			// note: the signature is automatically captured
			srv.bind("foo", &foo);

			// Binding a lambda function to the name "add".
			srv.bind("add", [](int a, int b) {
				return a + b;
			});

			// Run the server loop.
			srv.run();

			return 0;
		}


		int client() {
			// Creating a client that connects to the localhost on port 8080
			rpc::client client("127.0.0.1", 8080);

			// Calling a function with paramters and converting the result to int
			auto result = client.call("add", 2, 3).as<int>();
			client.call("foo");
			std::cout << "The result is: " << result << std::endl;
			return 0;
		}
	}	

}
