#include "ClientApplication.hpp"
#include <cstdlib>
#include "UniversalException.h"

namespace Client
{
	ClientApplication* ClientApplication::instancePointer_ = nullptr;

	ClientApplication::ClientApplication()
	{

	}

	void ClientApplication::Init(int argc, char* argv[])
	{
		std::atexit(ClientApplication::ExitHandler);
	}

	int ClientApplication::Run()
	{
		return 1;
	}
	
	void ClientApplication::ExitHandler()
	{

	}
}
