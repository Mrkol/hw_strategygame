#pragma once

#ifndef CLIENT_GAME_LOGIC_HPP_
#define CLIENT_GAME_LOGIC_HPP_

#include "Camera.hpp"
#include "UserInputManager.hpp"
#include "MatchManager.hpp"
#include "Network/Client.hpp"
#include "Network/Server.hpp"

namespace Client
{
	class GameLogic
	{
	public:
		GameLogic();

		void Init(Graphics::UserInputManager& inputManager);

		void Update();

		std::shared_ptr<Common::MatchManager> GetMatchManager();

		std::shared_ptr<Graphics::Camera> GetCamera();

		void StartGame(std::string adress);

		~GameLogic();

	private:
		bool keyUp_;
		bool keyDown_;
		bool keyLeft_;
		bool keyRight_;

		int cameraShiftSpeed_;

		float targetScale_;

		bool remote_;

		std::shared_ptr<Graphics::Camera> camera_;
		std::unique_ptr<Common::Network::Client> client_;
		std::unique_ptr<Common::Network::Server> server_;
		std::shared_ptr<Common::MatchManager> matchManager_;
	};
}

#endif // CLIENT_GAME_LOGIC_HPP_
