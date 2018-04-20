#include "MatchManager.hpp"
#include <iostream>
#include <chrono>

namespace Common
{
	MatchManager::MatchManager()
	{
		tick_.reset(new CDefaultEvent);
		matchMode_ = init;
		tickRate_ = TimeIntervalType(5);
		lastTick_ = std::chrono::system_clock::now();
	}

	void MatchManager::Start()
	{
		if (matchMode_ == end)
		{
			return;
		}
		matchMode_ = normal;
	}

	void MatchManager::Pause()
	{
		if (matchMode_ == end)
		{
			return;
		}
		matchMode_ = pause;
	}

	void MatchManager::Stop()
	{
		matchMode_ = end;
	}

	bool MatchManager::GenerateTick()
	{
		if (matchMode_ != normal)
		{
			return false;
		}
		
		if (lastTick_ + tickRate_ < std::chrono::system_clock::now())
		{
			lastTick_ = std::chrono::system_clock::now();
			tick_->Happen(EventArg());
			return true;
		}

		return false;
	}

	EMatchMode MatchManager::GetMode()
	{
		return matchMode_;
	}

	void MatchManager::SubscribeTick(bool(*func)(EventArg&))
	{
		tick_->Subscribe(func);
	}
}
