#pragma once

#ifndef COMMON_MATCH_MANAGER_HPP_
#define COMMON_MATCH_MANAGER_HPP_

#include "network.hpp"
#include "CommonHelper.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include <memory>
#include <chrono>

namespace Common
{
	enum class MatchState
	{
		Initialization, InProgress, Paused, Ended
	};

	enum class ClientType
	{
		Server, Client
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

		virtual ClientType GetClientType();

		virtual bool SetClientType(ClientType type);

		EventAccessProxy GameTickEvent;

	protected:
		MatchState currentMatchState_;
		TimeIntervalType tickRate_;
		TimePointType lastTick_;
		ClientType clientType_;

	};
}

#endif //COMMON_MATCH_MANAGER_HPP_
