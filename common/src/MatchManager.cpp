#include "MatchManager.hpp"
#include <ctime>
#include <iostream>

namespace Common
{
	MatchManager::MatchManager()
	{
		tick_.reset(new CDefaultEvent);
		matchMode_ = init;
		tickRate_ = 1;
		lastTick_ = 0;
	}

	void MatchManager::Start()
	{
		matchMode_ = normal;
	}

	void MatchManager::Pause()
	{
		matchMode_ = pause;
	}

	void MatchManager::Stop()
	{
		matchMode_ = end;
	}

	void MatchManager::GenerateTick()
	{
		if (matchMode_ != normal)
		{
			return;
		}
		time_t rawtime_;
		time(&rawtime_);
		if (lastTick_ + tickRate_ < rawtime_)
		{
			tick_->Happen(EventArg());
			lastTick_ = rawtime_;
		}
	}

	EMatchMode MatchManager::GetMode()
	{
		return matchMode_;
	}
}
