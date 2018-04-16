#include "MatchManager.hpp"
#include <ctime>

namespace Common
{
	MatchManager::MatchManager()
	{
		tick_.reset(new CDefaultEvent);
	}

	void MatchManager::Start()
	{

	}

	void MatchManager::GenerateTick()
	{
		time_t rawtime_;
		time(&rawtime_);
		if (lastTick_ + tickRate_ >= rawtime_)
		{
			tick_->Happen(EventArg());
			lastTick_ = tickRate_;
		}
	}
}
