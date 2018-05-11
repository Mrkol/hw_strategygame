#include "ClientApplication.hpp"
#include <cstdlib>
#include "UniversalException.hpp"

namespace Client
{
	ClientApplication* ClientApplication::instancePointer_ = nullptr;

	ClientApplication::ClientApplication()
	{

	}

	void ClientApplication::Init(int argc, char* argv[])
	{
		if (ClientApplication::instancePointer_)
		{
			throw Common::UniversalException()
				<< "Can't have two instances of an application active at the same time!";
		}
		std::atexit(ClientApplication::ExitHandler);

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw Common::UniversalException()
				<< "SDL could not initialize! SDL_Error:" << std::endl
				<< SDL_GetError() << std::endl;
		}

	}

	int ClientApplication::Run()
	{
		return 1;
	}
	
	void ClientApplication::ExitHandler()
	{

	}
}
