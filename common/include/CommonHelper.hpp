#pragma once

#ifndef COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
#define COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_

#include <memory>
#include <unordered_map>
#include <string>
#include <chrono>

namespace Common
{
	class EntityType;

	using EntityTypeRegistry = 
		std::unordered_map<std::string, std::shared_ptr<EntityType>>;

	using EntityInstanceIdType = unsigned int;
	using HealthType = unsigned int;
	using ManaType = unsigned int;
	using TimeUnitType = long long int;
	using TimeIntervalType = std::chrono::milliseconds;
	using TimePointType = std::chrono::system_clock::time_point;
	using MoveSpeedType = float;

	enum class MovementType
	{
		None = 0, Ground, Air
	};

	using TeamIdType = unsigned int;
}

#endif // COMMON_ENTITY_SYSTEM_REGISTRIES_HPP_
