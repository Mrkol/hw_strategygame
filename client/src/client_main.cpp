#include "client_main.hpp"
#include <iostream>
#include "ClientApplication.hpp"

int main(int argc, char* argv[])
{
	try
	{
		Client::ClientApplication app;
		app.Init(argc, argv);
		return app.Run();
	}
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
	return -1;
}
