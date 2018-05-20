#include "GameLogic.hpp"
#include "SDL.hpp"

namespace Client
{
	GameLogic::GameLogic()
		: keyUp_(false), keyDown_(false), keyLeft_(false), keyRight_(false),
		cameraShiftSpeed_(10), targetScale_(1), remote_(false),
		client_(nullptr),
		server_(nullptr),
		camera_(nullptr),
		matchManager_(nullptr)
	{

	}

	void GameLogic::Init(Graphics::UserInputManager& inputManager)
	{
		// ya sejchas sdohnu
		camera_ = std::make_shared<Graphics::Camera>(800, 600);

		inputManager.OnKeyDown.Subscribe("camera", 
			[this](Common::Events::EventArgs& args)
			{
				Graphics::KeyboardEventArgs& casted = 
					dynamic_cast<Graphics::KeyboardEventArgs&>(args);

				if (casted.Key.scancode == SDL_SCANCODE_LEFT)
					keyLeft_ = true;
				if (casted.Key.scancode == SDL_SCANCODE_RIGHT)
					keyRight_ = true;
				if (casted.Key.scancode == SDL_SCANCODE_UP)
					keyUp_ = true;
				if (casted.Key.scancode == SDL_SCANCODE_DOWN)
					keyDown_ = true;
				
				if (casted.Key.scancode == SDL_SCANCODE_EQUALS && targetScale_ < 2)
					targetScale_ += 0.1;
				if (casted.Key.scancode == SDL_SCANCODE_MINUS && targetScale_ > 0.2)
					targetScale_ -= 0.1;
			});

		inputManager.OnKeyUp.Subscribe("camera", 
			[this](Common::Events::EventArgs& args)
			{
				Graphics::KeyboardEventArgs& casted = 
					dynamic_cast<Graphics::KeyboardEventArgs&>(args);

				if (casted.Key.scancode == SDL_SCANCODE_LEFT)
					keyLeft_ = false;
				if (casted.Key.scancode == SDL_SCANCODE_RIGHT)
					keyRight_ = false;
				if (casted.Key.scancode == SDL_SCANCODE_UP)
					keyUp_ = false;
				if (casted.Key.scancode == SDL_SCANCODE_DOWN)
					keyDown_ = false;
			});

		matchManager_ = std::make_shared<Common::MatchManager>();
	}

	void GameLogic::Update()
	{
		if (keyLeft_) camera_->Shift(-cameraShiftSpeed_, 0);
		if (keyRight_) camera_->Shift(cameraShiftSpeed_, 0);
		if (keyUp_) camera_->Shift(0, -cameraShiftSpeed_);
		if (keyDown_) camera_->Shift(0, cameraShiftSpeed_);

		while (camera_->GetScale() < targetScale_) camera_->IncrementScale(0.01);
		while (camera_->GetScale() > targetScale_) camera_->IncrementScale(-0.01);


		matchManager_->GenerateTick();
	}

	std::shared_ptr<Graphics::Camera> GameLogic::GetCamera()
	{
		return camera_;
	}

	std::shared_ptr<Common::MatchManager> GameLogic::GetMatchManager()
	{
		return matchManager_;
	}

	void GameLogic::StartGame(std::string adress)
	{
		matchManager_->Start(adress.empty());

		if (adress.empty())
		{
			// client_ = std::make_unique<Common::Network::Client>();
			remote_ = true;
		}
		else
		{
			// server_ = std::make_unique<Common::Network::Server>();
		}
	}


	GameLogic::~GameLogic()
	{
		camera_.reset();
		matchManager_.reset();
	}
}
