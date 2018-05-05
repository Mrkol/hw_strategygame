#include "MatchManager.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include <iostream>
#include <chrono>

namespace Common
{
	MatchManager::MatchManager()
		: gameTick_(),
		GameTickEvent(gameTick_),
		currentMatchState_(MatchState::Initialization),
		tickRate_(TimeIntervalType(5)),
		clientType_(ClientType::Server)
	{
		
	}

	ClientType MatchManager::GetClientType()
	{
		return clientType_;
	}

	bool MatchManager::SetClientType(ClientType type)
	{
		if (currentMatchState_ == MatchState::Initialization)
		{
			clientType_ = type;
			return true;
		}
		return false;
	}

	void MatchManager::Start()
	{
		if (currentMatchState_ == MatchState::Ended)
		{
			return;
		}
		currentMatchState_ = MatchState::InProgress;
	}

	void MatchManager::Pause()
	{
		if (currentMatchState_ == MatchState::Ended)
		{
			return;
		}
		currentMatchState_ = MatchState::Paused;
	}

	void MatchManager::Stop()
	{
		currentMatchState_ = MatchState::Ended;
	}

	bool MatchManager::GenerateTick()
	{
		if (currentMatchState_ != MatchState::InProgress)
		{
			return false;
		}
		
		if (lastTick_ + tickRate_ < std::chrono::system_clock::now())
		{
			lastTick_ = std::chrono::system_clock::now();
			gameTick_.Trigger(EventArgs());
			return true;
		}

		return false;
	}

	MatchState MatchManager::GetCurrentState()
	{
		return currentMatchState_;
	}
}
