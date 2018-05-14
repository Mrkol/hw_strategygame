#include "ClientApplication.hpp"
#include <cstdlib>
#include "UniversalException.hpp"

namespace Client
{
	ClientApplication* ClientApplication::instancePointer_ = nullptr;

	ClientApplication::ClientApplication()
		: done_(false), renderer_(nullptr), window_(nullptr)
	{

	}

	void ClientApplication::Init(int argc, char* argv[])
	{
		if (ClientApplication::instancePointer_)
		{
			throw Common::UniversalException()
				<< "Can't have two instances of an application active at the same time!";
		}
		ClientApplication::instancePointer_ = this;
		std::atexit(ClientApplication::ExitHandler);

		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw Common::UniversalException()
				<< "SDL could not initialize! SDL_Error:" << std::endl
				<< SDL_GetError() << std::endl;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);


		window_ = SDL_CreateWindow(
			"Strategygame",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			1080, 720,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
			);

		if (window_ == nullptr)
		{
			throw Common::UniversalException()
				<< "Window could not be created! SDL_Error:" << std::endl
				<< SDL_GetError() << std::endl;
		}

		renderer_ = std::make_unique<Graphics::GlobalRenderer>();

		renderer_->Init(window_);
	}

	int ClientApplication::Run()
	{
		while (!done_)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					done_ = true;
				}

				if (event.type == SDL_WINDOWEVENT)
				{
					if (event.window.event == SDL_WINDOWEVENT_RESIZED)
					{
						renderer_->OnResized(event.window.data1, event.window.data2);
					}
				}
			}

			renderer_->Render();
			SDL_GL_SwapWindow(window_);
		}

		return 0;
	}

	ClientApplication::~ClientApplication()
	{
		renderer_.reset();
		SDL_DestroyWindow(window_);
		SDL_Quit();
	}
	
	void ClientApplication::ExitHandler()
	{
		//do something
	}
}
