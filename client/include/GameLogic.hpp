#pragma once

#ifndef CLIENT_GAME_LOGIC_HPP_
#define CLIENT_GAME_LOGIC_HPP_

#include "Camera.hpp"
#include "UserInputManager.hpp"

namespace Client
{
	class GameLogic
	{
	public:
		GameLogic();

		void Init(Graphics::UserInputManager& inputManager,
			std::shared_ptr<Graphics::Camera> camera);

		void Update();

		~GameLogic();

	private:
		bool keyUp_;
		bool keyDown_;
		bool keyLeft_;
		bool keyRight_;

		int cameraShiftSpeed_;

		float targetScale_;


		std::shared_ptr<Graphics::Camera> camera_;	
	};
}

#endif // CLIENT_GAME_LOGIC_HPP_
