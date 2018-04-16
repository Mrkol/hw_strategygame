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
	class MatchManager
	{
	public:
		MatchManager();
		void Start(); // Begin generating gametick events
	private:
		TimeIntervalType tickRate_;
		time_t lastTick_;
		std::shared_ptr<IEvent> tick_;
		void GenerateTick();
	};
}

#endif COMMON_MATCH_MANAGER_HPP_