#pragma once

#ifndef COMMON_MATCH_MANAGER_HPP_
#define COMMON_MATCH_MANAGER_HPP_

#include "CommonHelper.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include "RakNet/RakPeer.h"
#include <memory>
#include <chrono>

namespace Common
{
	enum class MatchState
	{
		Initialization, InProgress, Paused, Ended
	};

	using namespace Events;

	class MatchManager
	{
		Event gameTick_;

	public:
		MatchManager();

		/**
		 * \brief Begin generating gametick events
		 */
		virtual void Start();

		/**
		 * \brief Stop generating gametick events
		 */
		virtual void Pause();

		/**
		 * \brief End match
		 */
		virtual void Stop();

		virtual bool GenerateTick();

		virtual MatchState GetCurrentState();

		EventAccessProxy GameTickEvent;

	protected:
		MatchState currentMatchState_;
		TimeIntervalType tickRate_;
		TimePointType lastTick_;

	};
}

#endif //COMMON_MATCH_MANAGER_HPP_
