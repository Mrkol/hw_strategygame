#pragma once

#ifndef COMMON_MATCH_MANAGER_HPP_
#define COMMON_MATCH_MANAGER_HPP_

#include "CommonHelper.hpp"
#include "Events/event.hpp"
#include "Events/EventAccessProxy.hpp"
#include <memory>
#include <chrono>
#include <vector>
#include <unordered_map>
#include "EntityInstance.hpp"
#include "Serialization\IEntityInstanceSerializer.hpp"
#include "EntityTypeBuilder.hpp"

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
		virtual void Start(bool remote);

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


		std::shared_ptr<EntityTypeBuilder> GetBuilder();
		std::shared_ptr<EntityTypeRegistry> GetRegistry();

		std::shared_ptr<EntityInstanceStorageType> GetInstanceStorage();

		EventAccessProxy GameTickEvent;

		bool UpdateInstance(EntityInstanceIdType id, const std::string& data,
			Serialization::IEntityInstanceSerializer& serializer);
	protected:
		MatchState currentMatchState_;
		TimeIntervalType tickRate_;
		TimePointType lastTick_;

		EntityInstanceIdType nextInstanceId_;

		bool isRemote_;

		std::shared_ptr<EntityTypeRegistry> entityTypeRegistry_;
		std::shared_ptr<EntityTypeBuilder> entityTypeBuilder_;
		std::shared_ptr<EntityInstanceStorageType> instanceList_;

	};
}

#endif //COMMON_MATCH_MANAGER_HPP_
