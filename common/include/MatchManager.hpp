#pragma once

#ifndef COMMON_MATCH_MANAGER_HPP_
#define COMMON_MATCH_MANAGER_HPP_

#include "CommonHelper.hpp"
#include "Events\IEvent.hpp"
#include "Events\CDefaultEvent.hpp"
#include <memory>
#include <chrono>

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
		virtual void Start(); // Begin generating gametick events
		virtual void Pause(); // Stop generating gametick events
		virtual void Stop(); // End match
		virtual bool GenerateTick();
		virtual EMatchMode GetMode();
		virtual void SubscribeTick(bool(*)(EventArg&));
	protected:
		EMatchMode matchMode_;
		TimeIntervalType tickRate_;
		TimePointType lastTick_;
		std::shared_ptr<IEvent> tick_;
	};
}

#endif //COMMON_MATCH_MANAGER_HPP_
