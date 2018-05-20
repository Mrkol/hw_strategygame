#pragma once

#ifndef CLIENT_CLIENT_APPLICATION_HPP_
#define CLIENT_CLIENT_APPLICATION_HPP_

#include <memory>
#include "GlobalRenderer.hpp"
#include "SDL.hpp"
#include "UserInputManager.hpp"
#include "GameLogic.hpp"

namespace Client
{
	using namespace Common::Events;

	class ClientApplication
	{
		Event onMouseMove_;
		Event onMouseButtonDown_;
		Event onMouseButtonUp_;
		Event onMouseWheel_;
		Event onMouseHWheel_;

		Event onKeyDown_;
		Event onKeyUp_;

	public:
		ClientApplication();

		void Init(int argc, char* argv[]);

		int Run();

		~ClientApplication();

	private:
		static void ExitHandler();

		static ClientApplication* instancePointer_;

		bool done_;
		std::unique_ptr<Graphics::GlobalRenderer> renderer_;
		std::unique_ptr<GameLogic> gameLogic_;
		Graphics::UserInputManager inputManager_;
	};
}

#endif // CLIENT_CLIENT_APPLICATION_HPP_
