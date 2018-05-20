#pragma once

#ifndef COMMON_MATCH_MANAGER_HPP_
#define COMMON_MATCH_MANAGER_HPP_

#include "Network/network.hpp"
#include "CommonHelper.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include <memory>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "EntityInstance.hpp"
#include "Serialization\IEntityInstanceSerializer.hpp"

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
	public:
		MatchManager();

		MatchManager(ClientType type, const std::vector<std::string>& adresses);
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

		EventAccessProxy GameTickEvent;

		bool UpdateInstance(EntityInstanceIdType id, const std::string& data,
			Serialization::IEntityInstanceSerializer& serializer);
	protected:
		MatchState currentMatchState_;
		Event gameTick_;
		TimeIntervalType tickRate_;
		TimePointType lastTick_;
		ClientType clientType_;
		EntityInstanceStorageType instanceList;
		EntityTypeRegistry entityTypeRegistry_;
		EntityInstanceIdType nextInstanceId;

	};
}

#endif //COMMON_MATCH_MANAGER_HPP_
