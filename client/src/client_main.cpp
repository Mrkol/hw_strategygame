#include "client_main.hpp"
#include "ClientApplication.hpp"

int main(int argc, char* argv[])
{
	ClientApplication app;
	app.Init(argc, argv);
	return app.Run();
}
