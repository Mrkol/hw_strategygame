#pragma once

#ifndef CLIENT_CLIENT_APPLICATION_HPP_
#define CLIENT_CLIENT_APPLICATION_HPP_

#include <memory>
#include "GlobalRenderer.hpp"
#include "SDL.h"


namespace Client
{
	class ClientApplication
	{
	public:
		ClientApplication();

		void Init(int argc, char* argv[]);

		int Run();

	private:
		static void ExitHandler();

		static ClientApplication* instancePointer_;

		std::unique_ptr<Graphics::GlobalRenderer> renderer_;
		std::shared_ptr<SDL_Window> window_;
	};
}

#endif // CLIENT_CLIENT_APPLICATION_HPP_
