#include "ClientApplication.hpp"
#include <cstdlib>
#include "UniversalException.hpp"
#include "Components/position.hpp"
#include "Components/renderer.hpp"
#include <iostream>
#include <thread>
#include "Serialization\ProtobufEntityInstanceSerializer.hpp"

namespace Client
{
	void NetPart(std::shared_ptr<Common::MatchManager> manager)
	{
		char t = 0;
		std::cout << "If you want to start server, type 0\nAnd if you wont to run client, type anything else\n";
		std::cin >> t;
		if (t == '0')
		{
			Common::Network::Server server({ "127.0.0.1" }, 8080, manager->GetInstanceStorage());
			manager->GameTickEvent.Subscribe("s", [&server](Common::EventArgs&)
			{
				server.SynchronizeClients(Common::Serialization::ProtobufEntityInstanceSerializer());
			});
			
		}
		else
		{
			Common::Network::Client client(8080, manager);
			client.Start();
		}
	}

	ClientApplication* ClientApplication::instancePointer_ = nullptr;

	ClientApplication::ClientApplication()
		: 
		done_(false), renderer_(nullptr), gameLogic_(nullptr),
		inputManager_(onMouseMove_, onMouseButtonDown_, onMouseButtonUp_,
			onMouseWheel_, onMouseHWheel_, onKeyDown_, onKeyUp_)
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


		gameLogic_ = std::make_unique<GameLogic>();
		gameLogic_->Init(inputManager_);

		renderer_ = std::make_unique<Graphics::GlobalRenderer>();
		renderer_->Init(inputManager_, gameLogic_->GetMatchManager()->GetInstanceStorage(),
			gameLogic_->GetCamera());



		auto builder = gameLogic_->GetMatchManager()->GetBuilder();

		builder->StartBuilding("mage");
		builder->AddComponent(
			std::make_shared<Common::Components::PositionComponent>());
		builder->AddComponent(
			std::make_shared<Graphics::Components::RendererComponent>(
				renderer_->GetEntityAtlas(), 2, 0));
		builder->FinishBuilding();

		builder->StartBuilding("warrior");
		builder->AddComponent(
			std::make_shared<Common::Components::PositionComponent>());
		builder->AddComponent(
			std::make_shared<Graphics::Components::RendererComponent>(
				renderer_->GetEntityAtlas(), 2, 1));
		builder->FinishBuilding();

		std::thread thr(NetPart, gameLogic_->GetMatchManager());

		gameLogic_->StartGame("kek");
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

				switch (event.type)
				{
					case SDL_WINDOWEVENT:
						if (event.window.event == SDL_WINDOWEVENT_RESIZED)
						{
							renderer_->OnResized(event.window.data1, event.window.data2);
						}
						break;

					case SDL_MOUSEMOTION:
						{
							Graphics::MouseMoveEventArgs 
								moveArgs(event.motion.x, event.motion.y);
							onMouseMove_.Trigger(moveArgs);
						}
						break;

					case SDL_MOUSEBUTTONDOWN:
						{
							Graphics::MouseButtonEventArgs 
								buttonArgs(event.button.x, 
									event.button.y, event.button.button);
							onMouseButtonDown_.Trigger(buttonArgs);
						}
						break;

					case SDL_MOUSEBUTTONUP:
						{
							Graphics::MouseButtonEventArgs 
								buttonArgs(event.button.x, 
									event.button.y, event.button.button);
							onMouseButtonUp_.Trigger(buttonArgs);
						}
						break;

					case SDL_MOUSEWHEEL:
						if (event.wheel.x > 0)
						{
							Graphics::MouseWheelEventArgs
								wheelArgs(0, 0, event.wheel.x);
							SDL_GetMouseState(&wheelArgs.X, &wheelArgs.Y);
							onMouseHWheel_.Trigger(wheelArgs);
						}
						
						if (event.wheel.y > 0)
						{
							Graphics::MouseWheelEventArgs
								wheelArgs(0, 0, event.wheel.y);
							SDL_GetMouseState(&wheelArgs.X, &wheelArgs.Y);
							onMouseHWheel_.Trigger(wheelArgs);
						}
						break;

					case SDL_KEYDOWN:
						{
							Graphics::KeyboardEventArgs
								keyboardArgs(event.key.keysym);
							onKeyDown_.Trigger(keyboardArgs);
						}
						break;

					case SDL_KEYUP:
						{
							Graphics::KeyboardEventArgs
								keyboardArgs(event.key.keysym);
							onKeyUp_.Trigger(keyboardArgs);
						}
						break;

					default:
						break;
				}
			}

			gameLogic_->Update();


			renderer_->Render();
		}

		return 0;
	}

	ClientApplication::~ClientApplication()
	{
		renderer_.reset();
		SDL_Quit();
	}
	
	void ClientApplication::ExitHandler()
	{
		//do something
	}
}
