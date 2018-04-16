#pragma once

#ifndef COMMON_MATCH_MANAGER_HPP_
#define COMMON_MATCH_MANAGER_HPP_

#include "CommonHelper.hpp"
#include "Events\IEvent.hpp"
#include "Events\CDefaultEvent.hpp"
#include <memory>
#include <ctime>

namespace Common
{
	enum EMatchMode
	{
		pause, normal, end, init
	};

	class MatchManager
	{
	public:
		MatchManager();
		void Start(); // Begin generating gametick events
		void Pause(); // Stop generating gametick events
		void Stop(); // End match
		void GenerateTick();
		EMatchMode GetMode();
		void SubscribeTick();
	private:
		EMatchMode matchMode_;
		TimeIntervalType tickRate_;
		time_t lastTick_;
		std::shared_ptr<IEvent> tick_;
	};
}

#endif COMMON_MATCH_MANAGER_HPP_
